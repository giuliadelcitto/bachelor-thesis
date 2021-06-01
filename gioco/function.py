import serial
from drawnow import *
import time
import pygame
from pygame import key
import math
import sys
import numpy as np

serialArduino = serial.Serial('/dev/ttyACM0', 19600)

class data():
	acc=[0,0,0]
	gyr=[0,0,0]
	mag=[0,0,0]
	tem=[0]

def read_data():
	while (serialArduino.inWaiting()==0):
		pass
	
	read=[[],[],[],[]]
	for i in range (0,4):
		read[i]=serialArduino.readline().split()

	#check if valid value can be casted
	try:
		linea_acc=[]
		linea_gyr=[]
		linea_mag=[]
		linea_tem=[]
		acc = [0,0,0]
		mag = [0,0,0]
		gyr = [0,0,0]
		tem = [0]
		
		if( ( len(read[0]) != 4 and len(read[0]) != 2 ) or (len(read[1]) != 4 and len(read[1]) != 2 ) or (len(read[2]) != 4 and len(read[2]) != 2 ) or (len(read[2]) != 4 and len(read[2]) != 2 )): 
			print("Errore lettura da seriale")
			return
			
		for i in range(0,4):
			if( int(read[i][0]) == 0):
				linea_acc=read[i]
			elif( int(read[i][0]) == 1):
				linea_gyr=read[i]
			elif( int(read[i][0]) == 2):
				linea_mag=read[i]
			elif( int(read[i][0]) == 3):
				linea_tem=read[i]
		
		
		for i in range(0,3):
			acc[i] = int(linea_acc[i+1]) / 100.0
			gyr[i] = int(linea_gyr[i+1]) / 100.0
			mag[i] = int(linea_mag[i+1]) / 100.0
			
		tem[0] = int(linea_tem[1])
		
		data.acc=acc
		data.gyr=gyr
		data.mag=mag
		data.tem=tem
		
	except ValueError:
		print ("Invalid! cannot cast")

def rotate(surface, angle, pivot, offset):
    rotated_image = pygame.transform.rotozoom(surface, angle, 1)  # Rotate the image.
    rotated_offset = offset.rotate(angle)  # Rotate the offset vector.
    # Add the offset vector to the center/pivot point to shift the rect.
    rect = rotated_image.get_rect(center=pivot+rotated_offset)
    return rotated_image, rect  # Return the rotated image and shifted rect.

def blitRotate(surf, image, pos, originPos, angle):
    w, h       = image.get_size()
    box        = [pygame.math.Vector2(p) for p in [(0, 0), (w, 0), (w, -h), (0, -h)]]
    box_rotate = [p.rotate(angle) for p in box]
    min_box    = (min(box_rotate, key=lambda p: p[0])[0], min(box_rotate, key=lambda p: p[1])[1])
    max_box    = (max(box_rotate, key=lambda p: p[0])[0], max(box_rotate, key=lambda p: p[1])[1])
    pivot        = pygame.math.Vector2(originPos[0], -originPos[1])
    pivot_rotate = pivot.rotate(angle)
    pivot_move   = pivot_rotate - pivot
    origin = (pos[0] - originPos[0] + min_box[0] - pivot_move[0], pos[1] - originPos[1] - max_box[1] + pivot_move[1])
    rotated_image = pygame.transform.rotate(image, angle)
    
    surf.blit(rotated_image, origin)

