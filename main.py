import platform
import sys
import time

def system_check():
    print("\n---------------------------------------")
    print("   S2T ROVER: SYSTEM INITIALIZATION    ")
    print("---------------------------------------")
    print(f"Hostname:    {platform.node()}")
    print(f"OS:          {platform.system()} {platform.release()}")
    print(f"Python Ver:  {sys.version.split()[0]}")
    print("---------------------------------------")
    print("Status:      ONLINE and READY.")
    print("---------------------------------------\n")

if __name__ == "__main__":
    system_check()