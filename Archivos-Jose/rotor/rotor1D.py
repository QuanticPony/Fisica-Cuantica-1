import numpy as np
import matplotlib as plt
import math as lm
import scipy as sc
import scipy.integrate as integral
import matplotlib.pyplot as plt

#abrimos un archivo para leer los datos
filein = open('config.txt','r')

variables=[]
cont=0
#leemos por lineas mirando solo la 2ª de cada 3
for line in filein:
    if cont%3==1:
        variables.append(line)
    cont+=1
filein.close()

#inicializamos las variables con la lista del fichero
L=int(variables[0])
nfun1=int(variables[1])
nfun2=int(variables[2])
dphi=float(variables[3])
Nest=int(variables[4])
#definimos la unidad compleja

#creamos la funcion de potencial que se empleará, los parámetros se cambian aqui
def V(phi):
    '''V(φ)=V₀·cos(nv·φ)'''    #forma funcional del potencial
    V0=20
    nv=2
    return V0*np.cos(nv*phi)

#Definimos la base de funciones que usaremos
def base(n,phi):
    '''exp(𝑖·n·φ)/√(2π)'''
    return np.exp(1j*n*phi)/np.sqrt(2*lm.pi)

#usaremos la funcion de integral de scipy
 

#esta funcion nos crea una matriz de las dimensiones dadas vacía
def domatrix(n,m):
    matrix=[]
    for i in range(n):
        a=[0]*m
        matrix.append(a)
    return matrix

#definimos variables intermedias de calculo
dim=2*L+1
H=domatrix(dim,dim)
print("Simulacion del OSCILADOR ARMONICO CUANTICO EN 1D")
print("usaremos un potencial de la forma: ",V.__doc__)
print("y empleamos la base: ",base.__doc__)
print("\nSe ha usado la siguiente configuración leida de ./config.txt:\n")

with open("config.txt",'r') as fconf:
    print(fconf.read())

#calculamos la matriz hamiltoniana
for l in range(dim):
    for m in range(l+1):
        H[l][m] = (integral.quad(lambda phi: (base(l-m,phi)*V(phi)).real, 0, 2*lm.pi))[0] + 1j*(integral.quad(lambda phi: (base(l-m,phi)*V(phi)).imag, 0, 2*lm.pi))[0]
        if l==m:
            H[l][m]+=(l-1)*(l-1)

for l in range(0,dim):
    for m in range(l,dim):
        H[l][m]=H[l][m]

aval,avec = np.linalg.eig(H)

print("\nAutovalores:")
for i in range(0,dim):
    print("\nλ",i,":\t",aval[i])

#calculamos la función de onda para las energías pedidas
def FDO(n,aval,avec,L,phi,time):
    func=0
    for i in range(-L,L+1):
        func+=avec[L+i][n]*base(i,phi) #valor estático
    func*=np.exp(-1j*aval[n]*time) #en una escala temporal ×ħ/2I
    return func


#hacemos los plots en t=0
phi=np.linspace(0,2*lm.pi,100)


fig, ax=plt.subplots()
for i in range(nfun1, nfun2+1):
    ax.plot(phi, (FDO(i,aval,avec,L,phi,0)).real, label=('estado '+str(i)))
ax.plot(phi, V(phi)/20, 'r--', label=V.__doc__)
ax.set_xlabel('φ')
ax.set_ylabel('Ψ(φ)')
ax.set_title('FDO\'s Rotor 1D')
ax.legend()
ax.grid()
plt.show()