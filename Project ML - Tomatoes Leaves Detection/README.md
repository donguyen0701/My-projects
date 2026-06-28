# Tomato Disease Doctor | Plant Disease Detection (Role: Solo Developer)

This repository contains my university project, developed as part of my Electrical and Computer Engineering (ECE) studies at Frankfurt University of Applied Sciences (FRA-UAS).

## 🖥️ About the Project

This project is an AI-powered diagnostic tool designed to help farmers quickly detect tomato plant diseases. It features a **Custom Convolutional Neural Network (CNN)** trained on the PlantVillage dataset to identify 10 different tomato leaf conditions, achieving a validation accuracy of over 89%. The backend logic is seamlessly integrated with a user-friendly Streamlit web interface for instant, real-time image diagnosis.

## 🛠️ Tools & Build Process

* Software & AI: The deep learning architecture was built and trained from scratch using **TensorFlow** and **Keras**. It utilizes dynamic data augmentation (rotations, flips, zooming) to prevent overfitting and ensure robust predictions.
* Frontend UI: A clean, interactive web application built with **Streamlit** that processes uploaded leaf images and outputs the top 3 most likely diagnoses with confidence scores.
* Performance Metrics: Includes automated scripts to generate evaluation metrics, classification reports, and confusion matrices using the `scikit-learn` and `seaborn` libraries.

## 🚀 How to Run

Requirements:
* Python 3.9 – 3.11
* Conda or a virtual environment
* Dataset and trained `.keras` model placed in the correct project directories. *(Note: Remember to update all directory paths in the scripts before running!)*

Instructions:
1.  Activate your environment: `conda activate tf_ml` (or `tf_ml\Scripts ctivate` for virtualenv).
2.  Install dependencies: `pip install -r requirements.txt`
3.  Run Model Evaluation & Report Export: `python MLCodes/generate_report_output.py` All output metrics and confusion matrices will be saved in the `PlantVillage/exports/` folder.
4.  Run the GUI Application: `streamlit run app.py`
5.  Open your browser at `http://localhost:8501` to use the application! Upload a plant leaf image (.jpg, .jpeg, .png) and click **Analyze** to view the predicted disease.
6.  To stop the application, press `CTRL + C` in the terminal.
