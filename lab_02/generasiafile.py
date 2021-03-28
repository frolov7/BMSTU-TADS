import random
n = int(input('Сколько строк должно быть в файле?:'))
name = ['Bolshoi','Mariana','Sovremenik','Alexandrinsky', 'Winter']
perfomance = ['Hamlet','Midsummer','Viy','Clowns','Sadko']
producer = ['Stepanov','Nikolaev','Vasilev','Garin','Volchek']
pricelow = [300,400,500,600,700]
pricehigh = [800, 900,1000,1100,1200]
types = [1,2,3]
age = [7,8,9,10,11]
typechild = ['Fairytale', 'Play', 'Musical']
typeadult = ['Play','Drama','Comedy']
composers = ['Beethoven','Goethe','Shostakovich','Verstovsky','Glinka','Khachaturian']
country = ['Russia','Germany','Franc', 'Japon','Kazakhstan','Ukrain']
minage = [5,9,14,18]
duration = [120,90,60,150, 200]
name1 = 'theathre_2.txt'
for i in range(n+1):
    flagrandom = random.randint(1,3)
    s = str(i+1)+' '+ name[random.randint(0,4)] +' '+ perfomance[random.randint(0,4)]+' '+ producer[random.randint(0,4)]+' '+str(pricelow[random.randint(0,4)])+' '+str(pricehigh[random.randint(0,4)])+' '+str(flagrandom)
    if flagrandom == 1:
        s+= ' '+ str(age[random.randint(0,2)])+' ' + typechild[random.randint(0,2)]
    elif flagrandom == 2:
        s+= ' '+ typeadult[random.randint(0,2)]
    else:
        s+= ' '+composers[random.randint(0,5)]+' '+country[random.randint(0,5)]+' '+str(minage[random.randint(0,3)])+' '+str(duration[random.randint(0,4)])
    f = open(name1,'a')
    f.write(s+'\n')
    i+=1
    f.close
    
