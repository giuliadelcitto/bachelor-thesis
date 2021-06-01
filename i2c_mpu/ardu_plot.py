import serial
import matplotlib.pyplot as plt
import numpy as np
from drawnow import *
import time

serialArduino = serial.Serial('/dev/ttyACM0', 19600)

plt.ion()
plt.figure(figsize=(13,13))
cnt=0

a_values = [[],[],[]]
g_values = [[],[],[]]
m_values = [[],[],[]]
t_values = []

def plotValues():
		
	plt.subplot(4,1,1)
	plt.title('Accelerometro')
	plt.grid(True)
	plt.ylabel('Values')
	plt.ylim(-3, 3)
	plt.plot(a_values[0], 'rx-', label='AX', marker='o', color='blue')
	plt.plot(a_values[1], 'rx-', label='AY', marker='o', color='green')
	plt.plot(a_values[2], 'rx-', label='AZ', marker='o', color='red')
	plt.legend(loc='upper right')
	
	plt.subplot(4,1,2)
	plt.title('Giroscopio')
	plt.grid(True)
	plt.ylabel('Values')
	plt.ylim(-200, 200)
	plt.plot(g_values[0], 'rx-', label='GX', marker='o', color='blue')
	plt.plot(g_values[1], 'rx-', label='GY', marker='o', color='green')
	plt.plot(g_values[2], 'rx-', label='GZ', marker='o', color='red')
	plt.legend(loc='upper right')
	
	plt.subplot(4,1,3)
	plt.title('Magnetometro')
	plt.grid(True)
	plt.ylabel('Values')
	plt.ylim(-50, 50)
	plt.plot(m_values[0], 'rx-', label='MX', marker='o', color='blue')
	plt.plot(m_values[1], 'rx-', label='MY', marker='o', color='green')
	plt.plot(m_values[2], 'rx-', label='MZ', marker='o', color='red')
	plt.legend(loc='upper right')
	
	plt.subplot(4,1,4)
	plt.title('Temperatura')
	plt.grid(True)
	plt.ylabel('Values')
	plt.ylim(0, 54)
	plt.plot(t_values, 'rx-', label='MX', marker='o', color='blue')
	plt.legend(loc='upper right')
    	
def main():  
	for n in range(15):
		t_values.append(0)
		for i in range(3):
			a_values[i].append(0)
			g_values[i].append(0)
			m_values[i].append(0)
			
	while True:
		while (serialArduino.inWaiting()==0):
			pass
		
		read=[[],[],[],[]]
		for i in range (0,3):
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
			
			if ( ( len(read[0]) != 4 and len(read[0]) != 2 ) or (len(read[1]) != 4 and len(read[1]) != 2 ) or (len(read[2]) != 4 and len(read[2]) != 2 ) or (len(read[2]) != 4 and len(read[2]) != 2 )): 
				print("Errore lettura da seriale")
				continue
				
			for i in range(0,3):
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
				
			#tem[0] = int(linea_tem[1])
				
			for i in range(0,3):
				a_values[i].append(acc[i])
				g_values[i].append(gyr[i])
				m_values[i].append(mag[i])
			t_values.append(tem[0])

			for i in range(0,3):
				a_values[i].pop(0)
				g_values[i].pop(0)
				m_values[i].pop(0)
			t_values.pop(0)
			
			drawnow(plotValues)
			
			
		except ValueError:
			print ("Invalid! cannot cast")
		
if __name__ == '__main__' : main()
