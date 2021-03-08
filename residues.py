import multiprocessing as mp
import subprocess
import os
import platform

# directory to store csv files
RESIDUE_DIR = "residues"

# random generator settings
RANDOM_MIN = 1            # minimum value to generate
RANDOM_MAX = 150          # maximum value to generate
RANDOM_SIZE = 3000        # number of random numbers to generate
RANDOM_SEED = 1615011838  # seed for random number generator

# number of processes to spawn
NUM_WORKERS = 1 # number of processes to spawn (~number of cores)

# X range as integers (i.e. multiplied by 1000)
X_MIN = -1000
X_MAX = 1000

def run_worker(x):
  print(f"{x}: start")

  csv_file = os.path.join(RESIDUE_DIR, "residues%+d.csv" % x)

  # worker/xz paths
  if platform.system() == 'Windows':
    worker_cmd = "worker.exe"
    xz_cmd = os.path.join("utils", "xz.exe")
  else:
    worker_cmd = "./worker"
    xz_cmd = "xz"

  # run worker process
  ret = subprocess.call([worker_cmd, csv_file, str(x), str(RANDOM_MIN), str(RANDOM_MAX), str(RANDOM_SIZE), str(RANDOM_SEED)])

  # compress with xz
  if ret == 0:
    subprocess.call([xz_cmd, csv_file], shell=True)

  # return status
  if ret != 0:
    print(f"{x}: fail")
    return

  print(f"{x}: done")


def run():
  x_range = range(X_MIN, X_MAX + 1)

  with mp.Pool(NUM_WORKERS) as p:
    p.imap(run_worker, x_range)
    p.close()
    p.join()

if __name__ == "__main__":
  run()