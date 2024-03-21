from jetson_inference import detectNet
from jetson_utils import videoSource, videoOutput

net = detectNet(model="/home/grup8/Desktop/ELE495/5_obj_model/ssd-mobilenet.onnx", labels="/home/grup8/Desktop/ELE495/5_obj_model/labels.txt", input_blob="input_0", output_cvg="scores", output_bbox="boxes", threshold=0.5)
camera = videoSource("/dev/video0")  # '/dev/video0' for V4L2


while True:
    img = camera.Capture()

    while img is None: # capture timeout
        img = camera.Capture()
    
    detections = net.Detect(img)
        
    print("detected {:d} objects in image".format(len(detections)))
        
    for detection in detections:
        print(detection)
