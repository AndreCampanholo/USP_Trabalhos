# Fonte de Tensão Ajustável
Projeto desenvolvido para a disciplina [SSC0180 - Eletrônica para Computação], ministrada pelo Professor Eduardo do Valle Simôes.

# Integrantes do Grupo 13
| Aluno | Nº USP |
|---|---|
| André Campanholo Paschoalini | 14558061 |
| Eduardo Poltroniere da Silva | 16862892 |
| Felipe Fabiano das Chagas | 16811922 |
| Pedro Hamamoto da Palma | 16818280 |

# Explicação do Projeto
O circuito deve ser capaz de transformar uma tensão alternada de 127V em contínua, para o intervalo de 3V a 12V e entregar uma corrente de saída de 100mA, em que a regulagem de tensão deve ser feita através de um potenciômetro.

# Lista dos Componentes
Cabem aqui apenas os componentes adquiridos para a execução do trabalho, excetuando componentes emprestados ou que já eram de posse de algum integrante do grupo.
| Componente | Especificação | Quantidade | Preço |
|---|---|---|---|
| Potenciômetro | 1W B5K B-16 | 1 | R$ 7,00 |
| Capacitor | 470μF, 35V | 2 | R$ 5,60 |
| Transistor 2N3904 | 60V, 0.2A, 0.65W | 2 | R$ 3,20 |
| Resistor CR25 100 | 100Ω | 10 | R$ 0,70 |
| Resistor CR25 1.8K | 1800Ω | 10 | R$ 0,70 |
| Resistor CR25 2.2K | 2200Ω | 10 | R$ 0,70 |
| Resistor 120R | 120Ω, 5%, 5W | 2 | R$ 3,80 |
| Diodo | 1N4007 | 10 | R$ 2,00 |
| Diodo Zener | 1N4743 13V, 1W | 2 | R$ 1,00 |
| LED Vermelho | 5mm | 2 | R$ 1,00 |
| Jumper | Macho x Macho 20cm | 10 | R$ 7,00 |
| Total |   |   | R$ 32,70 |

# Função dos Componentes
**• Transformador:** O transformador é o componente responsável por diminuir a tensão de entrada do circuito para um valor mais próximo ao desejado. O transformador utilizado reduz a tensão de pico de 127V para uma de, aproximadamente, 18V. Nota-se que esta ainda não é a tensão exigida para o projeto, portanto o restante do circuito é moldado para que a tensão de saída permaneça no intervalo 3-12V.<br><br>
**• Ponte de Diodos:** Os diodos são componentes que permitem o fluxo unidirecional de corrente. Quando organizados na forma de ponte de diodos, atuam para manter o abastecimento de corrente em ambas as fases do fornecimento de tensão (semiciclo positivo e negativo). Após essa etapa, a voltagem é retificada (polaridade única) e torna-se pulsante.<br><br>
**• Capacitor:** Um capacitor armazena carga elétrica até determinada quantia, a depender da capacitância, após a qual esta carga é liberada. No circuito, o capacitor é responsável por filtrar a voltagem, reduzindo a amplitude da pulsação. A voltagem resultante assume a forma de um Ripple.<br><br>
**• Diodo Zener:** Um Diodo Zener, quando instalado no sentido da corrente, assim como um diodo normal, permite o fluxo unidirecional de corrente. Quando instalado no sentido contrário, atua como um retificador de tensão. Na fonte, o Zener é instalado no sentido reverso, portanto retifica a tensão para um valor constante, neste caso, de 13V.<br><br>
**• Transistor:** O transistor é um componente semicondutor capaz de amplificar ou atenuar a passagem da corrente elétrica pelo circuito. Esse dispositivo possui três terminais, os quais, na configuração NPN, têm as seguintes funções: base, responsável por controlar a corrente que flui entre o coletor e o emissor; emissor, local por onde a corrente elétrica entra; e coletor, terminal que libera a corrente de saída. Sob a perspectiva do projeto, o ganho entre a corrente da base (Ib) e do coletor (Ic) é de, aproximadamente, cem vezes, possibilitando a existência da corrente elétrica desejada de 100mA na saída.<br><br>
**• Potenciômetro:** O potenciômetro é um componente com uma resistência variável. A resistência máxima do potenciômetro empregado é de 5kΩ, e sua função é regular, conforme a resistência aplicada, a tensão de saída do circuito (resistência mínima ---> 3V / resistência máxima ---> 12V).<br><br>
**• Resistores:** Resistores consomem tensão quando associados em série, e para limitar corrente quando ligados em paralelo. Neste caso, contribuem para auxiliar o circuito a atingir as exigências de corrente e tensão.<br><br>
**• LED:** Esse dispositivo indica a passagem de corrente onde foi instalado, então foi inserido para acusar o funcionamento da fonte para o usuário.<br><br>

# Circuito da Fonte
![Circuito_Falstad](https://github.com/user-attachments/assets/753f5140-2f8f-4558-91b9-41d9b97e7e20)
[Link do Circuito no falstad](https://tinyurl.com/2cjqocsm)

# Circuito no Protoboard - Vista Superior
![Circuito_Protoboard1](https://github.com/user-attachments/assets/ac1da0dd-7930-468d-b1b4-476971e12a93)

# Circuito no Protoboard - Vista Frontal
![Circuito_Protoboard2](https://github.com/user-attachments/assets/5a615ed1-d733-4367-8e0f-ed9c118c0db6)

# EAGLE - Esquemático do Circuito 
![EAGLE_Esquematico](https://github.com/user-attachments/assets/f0c94348-775d-4e4a-9912-604963d73fee)

# EAGLE - Placa de Circuito Impresso (PCB)
![EAGLE_PCB](https://github.com/user-attachments/assets/ca3a65e0-cf54-4e7a-9ae3-f715dc206810)

# Vídeos
Funcionamento: https://youtube.com/shorts/StS6TcGJtbc?feature=share<br><br>
Explicação : https://youtube.com/shorts/VfgMIqr5M_I?feature=share

# Cálculos

**• Razão das Espiras do transformador:** Para esse cálculo, utilizamos a fórmula: Vp/Vs = Np/Ns, sendo Np = Número de espiras no primário e Ns o número de espiras no secundário. Assim, temos: 127/18 ≈ 7,05

**• Tensão de Pico:** A tensão inicial foi de 127V, logo, a tensão de pico é 127 * √2 ≈ **179,6V**

**• Tensão total no capacitor:** Para isso, vamos calcular a tensão de pico utilizando tensão da bobina secundária (18V), 18 * √2 ≈ **25,45V**, essa seria a tensão ideal.
Após isso, para calcular a tensão total do capacitor, temos que considerar as perdas do diodo, Vp - Vperdida = 25,45 - (2 * 0,7V) = **24,05V** 

**• Corrente total do circuito:** Visto que o circuito é uma fonte de 12V a 3V, e medimos isso num resistor de 120Ω, podemos facilmente calcular a corrente pela 1º lei de ohm: U = R * I -> 12 = 120 * I, I = **100mA** ou 3 = 120 * I, I = **25mA**

**• Tensão no ripple e capacitância:** Para a tensão de ripple, vamos limitá-lo a 10% da tensão do circuito, sendo assim: Vripple : Vtotal * 0,10 = 24,05 * 0,1 = **2,405V**
Agora consideraremos a fórmula para calcular a capacitância: C = I / 2 * f * V; Nesse caso, temos I como corrente total do circuito (≈102mA, valor obtido pelo falstad, diferente do valor ideal calculado acima), f = frequência de 60Hz, da tomada e V = Nesse caso vamos utilizar o Vripple calculado anteriormente. Com isso, a conta fica: C = 102 * 10^-3 / 2 * 60 * 2,405 ≈ **353 * 10^-6 F ou 353μF**. Desse modo, o capacitor comercial escolhido foi o de **470μF**. 

**• Diodo Zener:** Resistência do diodo zener: Para esse cálculo, utilizaremos valores conhecidos do circuito, sendo a potência do zener (1W) e a tensão do zener(13V), usando a fórmula Pot = U * I. Isolando para I, temos: I = Pot / U -> I = 1 / 13  ≈ **77mA**

A fonte fornece 24,05V, e a saída precisa ser 13V(Tensão do Zener), logo a queda de tensão é de 11,05V. Com isso, para calcular a resistência mínima para ter essa tensão é preciso fazer : U = R * I -> R = U / I -> R = 11,05 / 77 * 10^-3 =  **143,5Ω**    

Agora para a resistência máxima: R * Imax = (Vtotal - Vripple) - Vzener -> R * Imax = 24,05 - 2,405 - 13 = 8,645V. Assim, podemos calcular Imax por : Ic + Iz + Ir, sendo Ic a corrente depois do pontênciometro (1mA), Iz a corrente que passa pelo Zener, como estamos calculando o caso de resistência máxima, a corrente do zener é 0. E por fim, o Ir que é a corrente que passa pelo resistor de 1,8K, abaixo do potenciometro (1,9mA, valor mostrado pelo Falstad)
Assim, podemos dizer que Imax = 1mA + 0 + 1,9mA = **2,9mA**. 

Agora, temos tudo o que precisamos para calcular a resistência máxima -> R * Imax = 8,645V -> R = 8,645 / 2,9 * 10^-3 -> Rmax = **2981Ω ou 2,981KΩ**
Essa resistência máxima indica qual o maior resistor que podemos colocar com o zener e o funcionamento continue igual, no caso do circuito, utilizamos um de 2,2KΩ

**• Tensão nos demais resistores:**
Por fim, o resistor de 4,4kΩ em série com o LED foi obtido ao unir dois resistores de 2,2kΩ em série; enquanto o resistor de 50Ω conectado ao coletor do transistor foi construído a partir da ligação em paralelo de dois resistores de 100Ω.
Podemos calcular a tensão e corrente deles:  Para o resistor de 4,4K, só é preciso retirar a tensão que o led "come", ficaria então 24,05 - 1,7 = **22,35V**, e com a lei de ohm, calculamos a corrente -> 22,35 = 4,4K * I -> I = **5mA**

Agora para o de 50 ohms, sabemos que a corrente do circuito é 100mA, então por lei de ohm -> U = R * I -> U = 50 * 0,1, U = **5V**

# Observação Técnica

• Ao testar o circuito completo no protoboard, verificou-se que a potência sobre os resistores de 100Ω, conectados em série com o coletor do transistor e em paralelo entre si, atingiu o limite suportado por tais dispositivos. Esse fato não comprometeu o funcionamento da fonte, a qual continuou alcançando o intervalo de tensão desejado, contudo, o calor dissipado por eles não é recomendado para testes práticos. Além disso, a tensão sobre o transistor também permaneceu no limite suportado, o que aumentou o calor emitido por tal componente. Portanto, o plano ideal seria trocar ambos os resistores por uma única resistência de 80Ω ou 120Ω que suporte 1W de potência, a fim de reduzir a tensão sobre o transistor e aplicar um resistor que suporte tal aumento em sua tensão.  
