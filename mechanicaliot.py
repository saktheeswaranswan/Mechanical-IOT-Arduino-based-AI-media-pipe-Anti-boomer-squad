import cv2
import serial
import time
import mediapipe as mp

arduino = serial.Serial('COM3', 9600, timeout=1)  # Replace with your port
time.sleep(2)  # Allow Arduino to initialize

mp_pose = mp.solutions.pose
pose = mp_pose.Pose()
cap = cv2.VideoCapture(0)

person_detected = False
last_seen_time = 0
last_sent = ""

def send_command(cmd):
    global last_sent
    if cmd != last_sent:
        arduino.write((cmd + "\n").encode())
        print(f"[Serial] Sent: {cmd}")
        last_sent = cmd

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = pose.process(rgb)

    current_time = time.time()

    if results.pose_landmarks:
        last_seen_time = current_time
        send_command("p")
    elif current_time - last_seen_time > 10:
        send_command("o")

    mp.solutions.drawing_utils.draw_landmarks(
        frame, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

    cv2.imshow("MediaPipe Detection", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

send_command("o")
cap.release()
cv2.destroyAllWindows()
arduino.close()

