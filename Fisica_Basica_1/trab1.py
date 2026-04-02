import math
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

#input dos dados
Vo = float(input("Informe a velocidade inicial da partícula em m/s: "))
theta = int(input("Informe o ângulo de inclinação do lançamento da partícula em graus: "))

#conversão de graus para radianos
theta = math.radians(theta)
theta_45 = math.radians(45)

# cálculo das componentes horizontais e verticais da velocidade inicial
Vox = Vo * math.cos(theta)
Voy = Vo * math.sin(theta)

#aceleração da gravidade em m/s
g = 9.8

#cálculos
R = (Vo**2 * math.sin(2 * theta)) / g  # Alcance
t_total = R / Vox  # Tempo de voo
H = (Voy * (t_total/2) - g * (t_total/2)**2 / 2)  # Altura máxima

#cálculos para theta = 45graus
R45 = (Vo**2 * math.sin(2 * theta_45)) / g
t45 = 2 * Vo * math.sin(theta_45) / g
H45 = (Vo**2 * math.sin(theta_45)**2) / (2 * g)

#impressão dos resultados
print(f"a) O alcance da partícula foi de R = {R:.2f}m.")
print(f"b) O tempo de vôo t = {t_total:.2f}s.")
print(f"c) A altura máxima atingida H = {H:.2f}m.")
print(f"d) Dado o mesmo Vo, caso θ = 45°, o alcance seria R = {R45:.2f}m e a altura máxima H = {H45:.2f}m.")

#configuração do gráfico
fig, ax = plt.subplots()
ax.set_xlim(0, R * 1.1)  # Margem de 10% no alcance
ax.set_ylim(0, H * 1.2)  # Margem de 20% na altura
ax.set_xlabel('Distância (m)')
ax.set_ylabel('Altura (m)')
ax.set_title('Trajetória da Partícula - Lançamento Oblíquo')
ax.grid(True)

#geração dos pontos da trajetória
t = np.linspace(0, t_total, 100)
x = Vox * t
y = Voy * t - 0.5 * g * t**2
ax.plot(x, y, 'b-', label='Trajetória')  # Trajetória em azul

#criação da partícula
particula, = ax.plot([], [], 'ro', label='Partícula')  # Ponto vermelho
ax.legend()

#função de inicialização da animação
def init():
    particula.set_data([], [])
    return particula,

#função de atualização da animação
def update(frame):
    particula.set_data(x[frame], y[frame])
    return particula,

#animação
ani = FuncAnimation(fig, update, frames=len(t), init_func=init, blit=True, interval=1000*t_total/len(t))

#exibição do gráfico
plt.show()