#! /usr/bin/env python3
#-*- coding:UTF-8 -*-
from __future__ import division

import cv2 as cv
import time
import numpy as np
import  glob
import os

#The frist step is to type in the path of the folder which contains images 
image_folder_path = '/Users/lucien/Desktop/cones_image/drive-download-20200910T181020Z-001'



# using class to realize function
class detect:
    def __init__(self):
        self.yellow_right = 0
        self.blue_right = 0

    # Histogram Equalization in R,G.B channels
    def hisEqulColor(self,img):
        ycrcb = cv.cvtColor(img, cv.COLOR_BGR2YCR_CB)
        channels = cv.split(ycrcb)
        cv.equalizeHist(channels[0], channels[0])
        cv.merge(channels, ycrcb)
        cv.cvtColor(ycrcb, cv.COLOR_YCR_CB2BGR, img)
        return img

    # sharpen the images, make them clearer
    def sharp(self,img):
        # apply for a sharpen kernel
        kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]], np.float32) 
        dst = cv.filter2D(img, -1, kernel=kernel)
        return img

    def bgd_remove(self,img,iteration_count):
        mask = np.zeros(img.shape[:2],np.uint8)
        bgdModel = np.zeros((1,65),np.float64)
        fgdModel = np.zeros((1,65),np.float64)

        #select area contains forebdg
        rect = (3,3,img.shape[1]-6,img.shape[0]-6)
        cv.grabCut(img,mask,rect,bgdModel,fgdModel,iteration_count,cv.GC_INIT_WITH_RECT)
        cv.imshow("1", mask)

        # mask ==2 means the bdg area and mask ==1 signify the fdg area you selected
        mask2 = np.where((mask==2)|(mask==0),0,1).astype('uint8')
         
        img = img*mask2[:,:,np.newaxis]#get the foreground
        return img

    def dectect_colour(self,img):
        color_box =[0,0,0,0]  #color_box[0] signify yellow, [1] signify blue, [2] signify black, [3] signify white

        min_pixel_available =10
        
        hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
        for row in range(hsv.shape[1]):
            for col in range(hsv.shape[0]):
                if (hsv[col,row][0] > 11 and hsv[col,row][0] <34 and hsv[col,row][1] >43 and hsv[col,row][1]<255 and hsv[col,row][2]>46 and hsv[col,row][2] <255):
                    
                    color_box[0] +=1
                if (hsv[col,row][0] > 100 and hsv[col,row][0] <124 and hsv[col,row][1] >43 and hsv[col,row][1]<255 and hsv[col,row][2]>46 and hsv[col,row][2] <255):
                    color_box[1] +=1  
                if (hsv[col,row][0] > 0 and hsv[col,row][0] <180 and hsv[col,row][1] >0 and hsv[col,row][1]<255 and hsv[col,row][2]>0 and hsv[col,row][2] <46):
                    color_box[2] +=1 
                if (hsv[col,row][0] > 0 and hsv[col,row][0] <180 and hsv[col,row][1] >0 and hsv[col,row][1]<30 and hsv[col,row][2]>221 and hsv[col,row][2] <255):
                    color_box[3] +=1             

        color_index = color_box.index(max(color_box))
        if (color_index == 0):
            print ("yellow")
            if (true_color == "yellow"):
                self.yellow_right +=1
                print ("right answear")
            else:
                print ("wrong answear")

        if color_index == 1:
            print ("blue")
            if (true_color == "blue"):
                self.blue_right +=1
                print ("right answear")
            else:
                print ("wrong answear")

        if color_index == 2:
            print ("black")
            if (true_color == "black"):
                print ("right answear")
            else:
                print ("wrong answear")        
        if color_index == 3:
            print ("white")
            if (true_color == "white"):
                print ("right answear")
            else:
                print ("wrong answear")               

    def get_yellow_right(self):
        return self.yellow_right

    def get_blue_right(self):
        return self.blue_right       




if __name__ == '__main__':
    IMAGE_PATH = image_folder_path  #This is the path of images folder
    paths = glob.glob(os.path.join(IMAGE_PATH, '*.png'))   # get all image with png in the whole folder
    paths.sort() # sort
 
    yellow_sum =0
    blue_sum =0
    detect = detect()  # create a instance of the class detect
    for path in paths:
        # get the true colour from the file name
        # later make comparation between it and the result
        true_color = path.split("/")[-1].split("_")[0]
        if (true_color =='yellow'):
            yellow_sum +=1
        if (true_color =='blue'):
            blue_sum +=1

        img= cv.imread(path)
        #img = detect.hisEqulColor(img)
        cv.imshow('original',img)
        img = detect.sharp(img)
        cv.imshow('sharp',img)
        img = detect.bgd_remove(img,5)
        cv.imshow('bgd_remove',img)

        detect.dectect_colour(img)
    
        cv.waitKey(1) 

    yellow_right = detect.get_yellow_right()
    blue_right = detect.get_blue_right()

    yellow_rate = yellow_right / yellow_sum
    blue_rate = blue_right / blue_sum
    

    print ("the percentage of good answers for yellow coins is %.2f  " %(yellow_rate))
    print ("the percentage of good answers for blue coins is %.2f " %(blue_rate))
    cv.destroyAllWindows()