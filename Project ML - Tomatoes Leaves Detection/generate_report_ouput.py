import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import os
from sklearn.metrics import classification_report, confusion_matrix

# Configurations
IMAGE_SIZE = 256
BATCH_SIZE = 32

VALID_PATH = "D:\\MLPresentation\\PlantVillage\\Valid"
MODEL_PATH = "D:\\MLPresentation\\PlantVillage\\plant_disease_model_improved.keras"
EXPORT_DIR = "D:\\MLPresentation\\PlantVillage\\exports"

os.makedirs(EXPORT_DIR, exist_ok=True)

# Load Data
print("Loading validation dataset...")
val_ds = tf.keras.utils.image_dataset_from_directory(
    VALID_PATH,
    image_size=(IMAGE_SIZE, IMAGE_SIZE),
    batch_size=BATCH_SIZE,
    shuffle=False
)

class_names = val_ds.class_names
num_classes = len(class_names)

# Load Model
print("Loading trained model...")
model = tf.keras.models.load_model(MODEL_PATH)

# Save Model Summary
summary_path = os.path.join(EXPORT_DIR, "model_summary.txt")
with open("model_report.txt", "w", encoding="utf-8") as f:
    model.summary(print_fn=lambda x: f.write(x + "\n"))

print(f" Model summary saved: {summary_path}")

model.compile(
    optimizer=model.optimizer,
    loss=tf.keras.losses.SparseCategoricalCrossentropy(),
    metrics=["accuracy"]
)

# Evaluation
print("Evaluating model...")
loss, acc = model.evaluate(val_ds, verbose=0)

eval_path = os.path.join(EXPORT_DIR, "evaluation.txt")
with open(eval_path, "w") as f:
    f.write(f"Validation Loss: {loss:.4f}\n")
    f.write(f"Validation Accuracy: {acc*100:.2f}%\n")

print(f"Evaluation saved: {eval_path}")

# Predictions
print("Generating predictions...")
y_true, y_pred, y_prob = [], [], []

for images, labels in val_ds:
    preds = model.predict(images, verbose=0)
    y_pred.extend(np.argmax(preds, axis=1))
    y_prob.extend(np.max(preds, axis=1))
    y_true.extend(labels.numpy())


# Classification Report
report = classification_report(
    y_true,
    y_pred,
    target_names=class_names,
    digits=4
)

report_path = os.path.join(EXPORT_DIR, "classification_report.txt")
with open(report_path, "w") as f:
    f.write(report)

print(f"Classification report saved: {report_path}")

#Confusion Matrix
cm = confusion_matrix(y_true, y_pred)

plt.figure(figsize=(12, 10))
sns.heatmap(
    cm,
    annot=True,
    fmt="d",
    cmap="Blues",
    xticklabels=class_names,
    yticklabels=class_names
)
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.title("Confusion Matrix")
plt.xticks(rotation=45, ha="right")
plt.tight_layout()

cm_path = os.path.join(EXPORT_DIR, "confusion_matrix.png")
plt.savefig(cm_path)
plt.close()

print(f"Confusion matrix saved: {cm_path}")

# Save raw predictions to CSV
csv_path = os.path.join(EXPORT_DIR, "predictions.csv")
with open(csv_path, "w") as f:
    f.write("true_label,predicted_label,confidence\n")
    for t, p, c in zip(y_true, y_pred, y_prob):
        f.write(f"{class_names[t]},{class_names[p]},{c:.4f}\n")

print(f"Predictions saved: {csv_path}")

print("\All training output exports!")
