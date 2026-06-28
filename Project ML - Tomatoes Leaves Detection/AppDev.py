import streamlit as st
import tensorflow as tf
import numpy as np
from PIL import Image
import os

# Configurations
IMAGE_SIZE = 256
MODEL_PATH = "D:\\MLPresentation\\PlantVillage\\plant_disease_model_improved.keras"

# These must be the 10 Tomato classes sorted Alphabetically to match how TensorFlow sees the folders.
CLASS_NAMES = [
    'Tomato___Bacterial_spot',
    'Tomato___Early_blight',
    'Tomato___Late_blight',
    'Tomato___Leaf_Mold',
    'Tomato___Septoria_leaf_spot',
    'Tomato___Spider_mites Two-spotted_spider_mite',
    'Tomato___Target_Spot',
    'Tomato___Tomato_Yellow_Leaf_Curl_Virus',
    'Tomato___Tomato_mosaic_virus',
    'Tomato___healthy'
]

NUM_CLASSES = len(CLASS_NAMES)

# Custom Streamlit App
# ===============================
st.set_page_config(
    page_title="Tomato Disease Doctor",
    page_icon="🍅",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Custom CSS to make the app look prettier
st.markdown("""
    <style>
    .main {
        background-color: #f5fdf5; /* Light green tint */
    }
    .stButton>button {
        color: white;
        background-color: #2e7d32; /* Dark Green */
        border-radius: 10px;
        height: 3em;
        width: 100%;
    }
    .reportview-container .main .block-container{
        padding-top: 2rem;
    }
    h1 {
        color: #1b5e20;
    }
    .prediction-box {
        padding: 20px;
        border-radius: 10px;
        background-color: white;
        box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2);
    }
    </style>
    """, unsafe_allow_html=True)

# Load Model
@st.cache_resource(show_spinner=False)
def load_trained_model():
    if not os.path.exists(MODEL_PATH):
        st.error(f"❌ Model file not found at {MODEL_PATH}")
        return None
    try:
        model = tf.keras.models.load_model(MODEL_PATH)
        return model
    except Exception as e:
        st.error("❌ Failed to load the model.")
        st.exception(e)
        return None

# Prediction Function ̣(We want top 3 predictions)
def predict_top_3(image: Image.Image, model):
    # Prepare Image
    image = image.convert("RGB")
    image = image.resize((IMAGE_SIZE, IMAGE_SIZE))
    img_array = tf.keras.preprocessing.image.img_to_array(image)
    img_array = np.expand_dims(img_array, axis=0) # (1, 256, 256, 3)

    # Get Predictions
    predictions = model.predict(img_array, verbose=0)[0] # Get 1D array
    
    # Get Top 3 (Sorted high to low)
    top_3_indices = np.argsort(predictions)[-3:][::-1]
    
    results = []
    for i in top_3_indices:
        results.append({
            "class": CLASS_NAMES[i],
            "score": float(predictions[i])
        })
    
    return results


# Main UI
# Sidebar Info
with st.sidebar:
    st.image("https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSLsEcsraB8Yh5vD5Us3MSDIpS2XE5hs8XNKA&s", width=100)
    st.title("About")
    st.info(
        """
        This AI tool helps farmers detect tomato plant diseases.
        
        Supported Diseases:
        - Bacterial Spot
        - Early/Late Blight
        - Leaf Mold
        - Mosaic Virus
        - Target Spot
        - Yellow Leaf Curl Virus
        - Spider Mites
        - Septoria Leaf Spot
        """
    )
    st.markdown("---")
    st.caption("Built with TensorFlow & Streamlit")

# Main Page
st.title("🍅 Tomato Disease Doctor")
st.markdown("**** Upload a leaf photo to get an instant diagnosis.")

# Layout: Upload on Left, Results on Right
col1, col2 = st.columns([1, 1.5], gap="large")

with col1:
    st.subheader("1. Upload Image")
    uploaded_file = st.file_uploader("", type=["jpg", "jpeg", "png"])
    
    if uploaded_file:
        image = Image.open(uploaded_file)
        st.image(image, caption="Uploaded Leaf", use_column_width=True)

with col2:
    st.subheader("2. Diagnosis Results")
    model = load_trained_model()
    
    if uploaded_file and model:
        if st.button("Analyze Leaf 🔍"):
            with st.spinner("Scanning for pathogens..."):
                top_3 = predict_top_3(image, model)
                
                # Extract Top Result
                top_result = top_3[0]
                top_name = top_result['class']
                top_score = top_result['score']
                
                # --- DISPLAY TOP RESULT ---
                st.markdown('<div class="prediction-box">', unsafe_allow_html=True)
                
                if "healthy" in top_name.lower():
                    st.success(f"*** 🌱 Result: {top_name}")
                    st.balloons() # Fun effect for healthy plants
                else:
                    st.error(f"*** ⚠️ Detected: {top_name}")
                
                st.markdown(f"**Confidence: {top_score*100:.2f}%**")
                st.progress(top_score)
                st.markdown('</div>', unsafe_allow_html=True)
                
                # --- DISPLAY OTHER POSSIBILITIES (TOP 2 & 3) ---
                st.markdown("*** Alternative Possibilities")
                st.caption("If the main result looks wrong, check these:")
                
                # Result 2
                res2 = top_3[1]
                st.write(f"**2. {res2['class']}** ({res2['score']*100:.1f}%)")
                st.progress(res2['score'])
                
                # Result 3
                res3 = top_3[2]
                st.write(f"**3. {res3['class']}** ({res3['score']*100:.1f}%)")
                st.progress(res3['score'])
                
    elif not uploaded_file:
        st.info("👈 Please upload an image to start.")