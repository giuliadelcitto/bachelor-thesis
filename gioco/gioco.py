import pygame
from pygame import key
import math
import sys
import numpy as np
from drawnow import *
import function

class Car(pygame.sprite.Sprite):

	linear_speed = 0
	rot_speed = 0
	angle = 0
	_base_image = None
	speed_mul = 1
	x_speed = None
	y_speed = None
	w,h = None, None
	screen = None
		
	def __init__(self, screen):
		super().__init__()
		self._base_image = pygame.image.load("car.png").convert_alpha()
		self.image = self._base_image
		self.image.set_colorkey(None)
		self.rect = self.image.get_rect()
		self.rect.center = [20, 40]
		self.w = self.image.get_size()[0]
		self.h = self.image.get_size()[1]
		self.screen = screen

	#speed è il vettore che moltiplica il vettore di steering    
	def update(self):
		w, h = self.image.get_size()
		self.angle = (self.angle+self.rot_speed)%360
		self.x_speed = -self.linear_speed*math.cos(math.radians((self.angle+90)%360))
		self.y_speed = self.linear_speed*math.sin(math.radians((self.angle+90)%360))

		self.rect.x = (self.rect.x + self.x_speed*self.speed_mul) % 1000
		self.rect.y = (self.rect.y + self.y_speed*self.speed_mul) % 1000
		
		function.blitRotate(screen, self.image, (self.rect.x, self.rect.y), (self.w/2 , self.h/5), self.angle)    

	def muovi(self, linear_speed_arr, rot_speed):
		acc_y=linear_speed_arr[1]
		acc_z=linear_speed_arr[2]
		if(acc_y>0):
			if (acc_z > 0):
				self.linear_speed =-((1- acc_y*acc_y)*20+20)
			else:
				self.linear_speed = (1- acc_y*acc_y)*20+20
		
		self.rot_speed = rot_speed 

WHITE = pygame.Color(255, 255, 255)
RED = pygame.Color(150, 0, 0)
GREEN = pygame.Color(30, 200, 0)
BLACK = pygame.Color(0,0,0)


pygame.init()
 
screen = pygame.display.set_mode((1500, 1000))
background_image = pygame.image.load("pista.png").convert_alpha()
screen.blit(background_image, [0,0])

clock = pygame.time.Clock()

car = Car(screen)
car.rect.x = 100
car.rect.y = 100

sprite_list = pygame.sprite.Group()
sprite_list.add(car)

while (1):
	function.read_data()
	print
	car.muovi(function.data.acc ,(function.data.gyr[2]))

	screen.fill(GREEN)
	screen.set_colorkey(None)


	screen.blit(background_image, [0,0])
	car.update()

	pygame.draw.line(screen, WHITE, [car._base_image.get_rect().x,car._base_image.get_rect().y], [car.x_speed, car.y_speed],2)
	pygame.draw.line(screen, BLACK, [1080,0], [1080,1000],5)

	dashboard = pygame.Rect(1080, 0, 1500, 1500)
	pygame.draw.rect(screen, BLACK,dashboard)

	pygame.draw.line(screen, RED, [1090, 10], [1090,990 ], 3)
	pygame.draw.line(screen, RED, [1490, 10], [1490,990 ], 3)
	pygame.draw.line(screen, RED, [1090, 10], [1490,10 ], 3)
	pygame.draw.line(screen, RED, [1090, 990], [1490,990 ], 3)
			
	pygame.draw.line(screen, RED, [1090, 240], [1490,240 ], 3)
	pygame.draw.line(screen, RED, [1090, 350], [1490,350 ], 3)
	pygame.draw.line(screen, RED, [1090, 670], [1490,670 ], 3)

	myfont = pygame.font.SysFont("monospace", 25)

	mag_label = myfont.render("MAGNETOMETRO", 1, (255,0,0))
	screen.blit(mag_label,(1100, 30))
	mag_label = myfont.render("X:" + str(function.data.mag[0]), 1, (255,0,0))
	screen.blit(mag_label,(1100, 80))
	mag_label = myfont.render("Y:" + str(function.data.mag[1]), 1, (255,0,0))
	screen.blit(mag_label,(1100, 140))
	mag_label = myfont.render("Z:" + str(function.data.mag[2]), 1, (255,0,0))
	screen.blit(mag_label,(1100, 190))
	
	temp_label = myfont.render("TEMPERATURA", 1, (255,0,0))
	screen.blit(temp_label,(1100, 250))
	temp_label = myfont.render(str(function.data.tem[0]), 1, (255,0,0))
	screen.blit(temp_label,(1100, 280))

	acc_label = myfont.render("ACCELEROMETRO", 1, (255,0,0))
	screen.blit(acc_label,(1100, 360))
	acc_label = myfont.render("X:" + str(function.data.acc[0]), 1, (255,0,0))
	screen.blit(acc_label,(1100, 440))
	acc_label = myfont.render("Y:" + str(function.data.acc[1]), 1, (255,0,0))
	screen.blit(acc_label,(1100, 520))
	acc_label = myfont.render("Z:" + str(function.data.acc[2]), 1, (255,0,0))
	screen.blit(acc_label,(1100, 600))

	gyro_label = myfont.render("GIROSCOPIO", 1, (255,0,0))
	screen.blit(gyro_label,(1100, 680))
	gyro_label_x = myfont.render("X:" +  str(function.data.gyr[0]), 1, (255,0,0))
	screen.blit(gyro_label_x,(1100, 760))
	gyro_label_y = myfont.render("Y:" +  str(function.data.gyr[1]), 1, (255,0,0))
	screen.blit(gyro_label_y,(1100, 840))
	gyro_label_z = myfont.render("Z:" +  str(function.data.gyr[2]), 1, (255,0,0))
	screen.blit(gyro_label_z,(1100, 920))

	pygame.display.flip()


	clock.tick(100)

	
