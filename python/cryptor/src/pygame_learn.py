# -*- coding: utf-8 -*-
'''
Created on 2012-4-2

@author: Sunday
'''

import pygame
from pygame.locals import *
from sys import exit

def dis_font_chinese():
    pygame.init()
    screen = pygame.display.set_mode((640,480) , 0 , 32)
    font   = pygame.font.Font("xing.ttf" , 40)
    text   = font.render(u'这TMD都是些什么字啊！！！！！~~~' , True , (0,0,0) )
    back   = pygame.image.load('hello.jpg').convert()
    
    x = 0
    y = (480 - text.get_height())/2
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                exit()
        
        screen.blit(back , (0,0))
#        x -= 1
#        if x < -text.get_width():
#            x = 640 - text.get_width()
        
        screen.blit(text , (10,20))
        pygame.display.update()
        
def event_info_print():
    pygame.init()
    SCREEN_SIZE = (640,480)
    screen = pygame.display.set_mode(SCREEN_SIZE , 0, 32)
    
    font = pygame.font.SysFont("arial", 16)
    font_height = font.get_linesize()
    event_text  = []
    
    while True:
        event = pygame.event.wait()
        event_text.append(str(event))
        event_text = event_text[-SCREEN_SIZE[1]/font_height:]
        
        if event.type == QUIT:
            exit()
        
        screen.fill((0,0,0))
        y = SCREEN_SIZE[1] - font_height
        
        for text in reversed(event_text):
            screen.blit( font.render(text, True , (0,255,0)) , (0,y))
            y -= font_height
        
        pygame.display.update()

def keyboard_movedown():
    faye_img = "hello.jpg"
    pygame.init()
    SCREEN_SIZE = (640,480)
    screen = pygame.display.set_mode(SCREEN_SIZE , 0 , 32)
    background = pygame.image.load(faye_img).convert()
    
    x, y = 0, 0
    move_x , move_y = 0,0
    
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                exit()
            if event.type == KEYDOWN:
                if event.key == K_LEFT:
                    move_x -= 10
                elif event.key == K_RIGHT:
                    move_x += 10
                elif event.key == K_UP:
                    move_y -= 10
                elif event.key == K_DOWN:
                    move_y += 10
            elif event.type == KEYUP:
                move_x = 0
                move_y = 0
            
            x += move_x
            y += move_y
            
            screen.fill( (0,0,0))
            screen.blit(background , (x,y))
            pygame.display.update()

def dis_color():
    pygame.init()
    screen = pygame.display.set_mode((640,480) )
    allcolo= pygame.Surface( (4096,4096) ,  0 , 24)
    for r in xrange(256):
        print r+1 , "out of 256"
        x = (r&15) *256
        y = (r>>4) * 256
        for g in xrange(256):
            for b in xrange(256):
                allcolo.set_at((x+g , y+b) , (r,g,b))
    pygame.image.save(allcolo, "allcolors.bmp")
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                exit()
            screen.fill( (0,0,0))
            screen.blit(allcolo , (0,0))
            pygame.display.update()
if __name__ == '__main__' :
    dis_color()