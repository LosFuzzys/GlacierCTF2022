import sys
import subprocess
import getopt

DEFAULT_FLAG = "\0glacierctf{But_g1rth_15_m0r3_1mp0rt4nt}\0"
KEYFRAME_FILE = "keyframes.txt"
WACKYWEBM_PATH = "WackyWebM/wackywebm.js"
#filename = sys.argv[1]

def help():
    print(f"Usage: {sys.argv[0]} <options> file.webm")
    print(f"Available options:")
    print(f"\t-s\t\tStop after creating keyframe file (don't create a video)")
    print(f"\t-o <file>\tSave the result to the specified file")
    print(f"\t-k <file>\tSave the keyframe information to the specified file")
    print(f"\t-f <flag>\tEncode the specified flag")
    print(f"\t-t <path>\tPath to the WackyWebM.js file")
    print(f"\t-h\t\tPrint this help")
    sys.exit(0)

wacky_options = ""
keyframe = KEYFRAME_FILE
flag = DEFAULT_FLAG
tool = WACKYWEBM_PATH
stop = False
opts, args = getopt.getopt(sys.argv[1:], "so:f:k:ht:")

for key, value in opts:
    if key == "-s": stop = True
    elif key == "-o": wacky_options += f" -o {value}"
    elif key == '-k': keyframe = value
    elif key == '-f': flag = value
    elif key == '-t': tool = value
    else: help()

if(len(args) != 1): help()

filename = args[0].strip()

# Requires ffmpeg
frame_proc = subprocess.check_output(f"ffprobe -v error -select_streams v:0 -count_frames -show_entries stream=nb_read_frames -print_format default=nokey=1:noprint_wrappers=1 {filename}".split(" "))
#frame_proc = subprocess.check_output(f"ffprobe")

frames = frame_proc.decode("ascii").strip()

dim_proc = subprocess.check_output(f"ffprobe -v error -select_streams v -show_entries stream=width,height -of csv=p=0:s=x {filename}".split(" "))


width, height = dim_proc.decode("ascii").strip().split("x")

print(width)
print(height)

frames_per_char = int(frames) // len(flag)

with open(keyframe, "w") as f:
    for i, c in enumerate(flag):
        f.write(f"0:{frames_per_char * i},{int(width) - ord(c)},{height},instant\n")

if stop: sys.exit(0)
print(f"node {tool}{wacky_options} keyframes+bounce -k {keyframe} {filename}")
subprocess.run(f"node {tool}{wacky_options} keyframes+bounce -k {keyframe} {filename}".split(" "))

