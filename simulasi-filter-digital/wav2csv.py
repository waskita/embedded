import sys, os, os.path
from scipy.io import wavfile
import pandas as pd

input_filename = "anti-aliasing-out.wav" # nama file input WAV, diganti jika file berbeda
output_filename= "anti-aliasing-out.csv" # nama output file CVS, diganti jika file berbeda
samrate, data = wavfile.read(str(input_filename))
wavData = pd.DataFrame(data)
wavData.columns = ['VIN', 'LPF_OUT']
wavData.to_csv(output_filename, mode='w')

