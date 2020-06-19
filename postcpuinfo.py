'''*
 * Filename     : <postcpuinfo.py>
 * Last Modified: 18 06 2020
 * Owner        : Group 20
 * 
 * Description: 
 * Python script to dump data in a database
 * Other: 
 * Make sure that you have benchmark.json otherwise the data won't go to the
 * database.
 *'''
import requests
import json
import os
#Try opening the file
try:
  with open('benchmark.json') as f: 
    dump = json.load(f) 
    print(str(dump))
    #Post the data
    r = requests.post("https://us-central1-raytracing-2c39f.cloudfunctions.net/api/benchmarks" , data = dump.get('entry') )
    #Print response status (Hope it is <Response [200]>)
    print(str(r))
    #Remove JSON dump after data has been posted
    os.remove('benchmark.json')
except:
  print("File already deleted")

