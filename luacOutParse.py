import re
import sys
import os

if len(sys.argv) > 1:
	textfile = open(sys.argv[1], 'r')
	lines = textfile.readlines()
	textfile.close()
	for i in lines:
		#i = i + "eol"
		j = re.sub(r"\t?[0-9]+\t+[][-]+\t([A-Z]+[ ]+?)\t?((-?[0-9]+ ?)+)(\t;)?(.+?)?\n", r"\1 \2", i)
		if i != j:
			i = os.popen('lbc52 ' + j).read()[:-1] + " | " + i[:-1] #+ "  --  " + j 
		#print(i[:-1])
		print(i)
