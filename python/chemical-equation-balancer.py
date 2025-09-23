# Alex Oliver 2025
# This code is in development and it will be able to balance unbalanced chemical equations to help me with my chemistry work and possibly kickstart a chemical reacting simulator. As of 23/09, this program only barely 'factorises' and makes sense of the inputed equation to seperate the compounds, reactants and products, along with subscripts. Brackets and subscripts will be added shortly but this code is rather unoptimised and full of bugs.

# Just realised by googling that this entire program could have been optimised using the split() function... Next time!

equation = "Cu+HNO^3->Cu(NO^3)^2+H^2O+NO^2"
products = {}
reactants = {}
subscript = False
isItReactants = True
compound = 0
chemicals = []
chemicalsInBrackets = []

for i in range(len(equation)):
    enumerate = equation[i]
    
    if enumerate.upper() == enumerate:
        j = i+1

        # find the entire chemical as len("K") (potassium) == 1 and len("Cu") (copper) == 2
        while j < len(equation):
            if equation[j] == equation[j].upper():
                break
            else:
                j += 1

        # multiply whats in the subscript (1 by default) by the subscript marked by ^
        if subscript:
            if isItReactants:
                reactants.setdefault(compound, {})[chemicals[len(chemicals)-2]] *= equation[i:j]
            else:
                products.setdefault(compound, {})[chemicals[len(chemicals)-2]] *= equation[i:j]
            
            subscript = False
        elif equation[i:j] == "+":
            compound += 1
        elif equation[i:j] == "-" or equation[i:j] == ">":
            isItReactants = False
        elif equation[i:j] == "^" and chemicals[len(chemicals)-1] != ")":
            subscript = True
        else:
            if isItReactants:
                reactants.setdefault(compound, {})[equation[i:j]] = 1
            else:
                products.setdefault(compound, {})[equation[i:j]] = 1
        
        chemicals.append(equation[i:j])

print("unblalanced:", equation)
print("reactants:", reactants)
print("products:", products)

