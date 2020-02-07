#!/usr/bin/python

import random, sys, argparse, string

def repeat(li, count):
	temp = li
	while len(temp) < count:
		temp = temp + li
	output = random.sample(temp, count)
	for x in output:
		print(x)

def main():
    parser = argparse.ArgumentParser(add_help=False, usage="shuf [OPTION]...\
    	[FILE] or shuf -i LO-HI [OPTION]...",
    	description="With no FILE, or when FILE is -, read standard input.\
    	\nWrite a random permutation of the input lines to standard output.")
    
    parser.add_argument('-n','--head-count', dest='count', metavar="COUNT", 
    	help="output at most COUNT lines")
    parser.add_argument('-r', '--repeat', dest='rep', action='store_true', 
    	help="output lines can be repeated")
    parser.add_argument('-i', '--input-range', dest='inputrange', metavar="LO-HI", 
    	help="treat each number LO through HI as an input line")
    parser.add_argument('--help', action='help', default=argparse.SUPPRESS,
    	help="show this help message and exit")
    parser.add_argument('filename', nargs='?', help="read lines from FILENAME")

    arg = parser.parse_args()
 
    #list to be permuted
    l = list()

    if(arg.inputrange != None and arg.filename != None):
    	sys.exit("shuf: extra operand '{}'".format(arg.filename))
    elif(arg.inputrange != None):
    	rangeList = arg.inputrange.split("-")
    	if(len(rangeList) != 2):
    		sys.exit("shuf: invalid input range: '{}'".format(arg.inputrange))
    	try:
    		low = int(rangeList[0])
    	except:
    		sys.exit("shuf: invalid input range: '{}'".format(arg.inputrange))
    	try:
    		high = int(rangeList[1])
    	except:
    		sys.exit("shuf: invalid input range: '{}'".format(arg.inputrange))
    	if low > high:
    		sys.exit("shuf: invalid input range: '{}'".format(arg.inputrange))

    	while low < (high+1):
    		l.append(low)
    		low += 1
    else:
    	if(arg.filename == "-" or \
    		arg.filename == "--" or arg.filename == None):
    		f = sys.stdin
    	else:
	    	try:
	    		f=open(arg.filename, 'r')
	    	except:
	    		sys.exit("shuf: '{}': No such file or directory".\
	    			format(arg.filename))

    	line = f.readline()
    	while line:
    		if "\n" in line:
    			l.append(line.replace("\n",''))
    		else:
    			l.append(line)
    		line = f.readline()
    	f.close()

    # infinite loop case
    if(arg.count == None and arg.rep):
    	while True:
    		print(random.sample(l,1)[0])

    if(arg.count != None):
    	try:
    		c = int(arg.count)
    	except:
    		sys.exit("shuf: invalid line count '{}'".format(arg.count))
    	if(c < 0):
    		sys.exit("shuf: invalid line count '{}'".format(c))
    	if(c > len(l)):
    		if(arg.rep):
    			repeat(l, c)
    		else:
    			repeat(l, len(l))
    	else:
    		repeat(l, c)
    else:
    	repeat(l, len(l))



if __name__ == "__main__":
    main()
