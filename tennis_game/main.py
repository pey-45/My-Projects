import pygame
import sys

pygame.init()
#const/var definition
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
#clock assignation
clock = pygame.time.Clock()
#mouse visibility
pygame.mouse.set_visible(False)
#window creation
screen_width = 800
screen_height = 500
screen = pygame.display.set_mode((screen_width, screen_height))

#other assignaments
x_ball = 200
y_ball = 250
x_ball_speed = 2
y_ball_speed = 2
ball_radius = 10
x_raquet_pos = 100
raquet_width = 20
raquet_height = 100
puntuacion = 0
record = 0

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    #posición actual del mouse
    mouse_pos = pygame.mouse.get_pos()[1]
    if mouse_pos > 400:
        mouse_pos = 400

    #dibujos
    screen.fill(WHITE)
    pygame.draw.rect(screen, BLACK, (x_raquet_pos, mouse_pos, raquet_width, raquet_height))
    pygame.draw.circle(screen, BLACK, (x_ball, y_ball), ball_radius+5)
    pygame.draw.circle(screen, (255, 255, 0), (x_ball, y_ball), ball_radius)

    #lógica
    x_ball += x_ball_speed
    y_ball += y_ball_speed
    if x_ball >= screen_width-ball_radius or (x_ball == x_raquet_pos+raquet_width+ball_radius and y_ball >= mouse_pos >= y_ball - raquet_height):
        x_ball_speed *= -1
        if x_ball == x_raquet_pos+raquet_width+ball_radius:
            puntuacion += 1
    if y_ball <= 0 or y_ball >= screen_height-ball_radius:
        y_ball_speed *= -1
    if x_ball <= -100:
        #valores de inicio
        x_ball = 200
        y_ball = 250
        x_ball_speed = 2
        y_ball_speed = 2
        if puntuacion > record:
            record = puntuacion
        puntuacion = 0

    fuente = pygame.font.Font(None, 50)
    punt = fuente.render("SCORE: " + str(puntuacion), True, BLACK)
    rec = fuente.render("BEST: " + str(record), True, BLACK)
    screen.blit(punt, (575, 25))
    screen.blit(rec, (609, 75))

    pygame.display.flip()
    clock.tick(144)