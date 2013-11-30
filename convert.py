#convert from JPG to PGM
#only in Python2.7
#Library download : http://www.pythonware.com/products/pil/index.htm
#Yanning 11/30

from os.path import walk, join, normpath
from os import chdir, remove
from PIL import Image

def scan(arg, dirname, names):
        for file in names:
                if file[-4:]==".jpg":                        
                        filename=dirname+file
                        print filename
                        im=Image.open(filename)
                        filename=file[:-4]
                        filename=dirname+filename
                        print filename
                        newname=filename+".pgm"
                        print newname
                        im.save(newname)
if __name__== "__main__": 
        walk("F:\\CSE484\\cse484project\\py\\",scan,0) #type in your JPG folder here
 
