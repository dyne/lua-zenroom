ECP = require'ecp'
BIG = require'big'
O = require'octet'

print()
print "= ELLIPTIC CURVE ARITHMETIC OPERATIONS TESTS FOR GENERIC TRANSFORMATIONS"
print()

g1 = ECP.generator()
o = ECP.order()

-- octet serialization back and forth
a = BIG.random() * ECP.generator() -- hashtopoint(O.random(64))
-- print("ECP serialized length: "..#a:octet().." bytes")
-- print(a:octet())
b = ECP.new(a:octet())
assert(a == b)

-- test mod_inverse
i = BIG.random()
inv = i:modinv(ECP.order())
assert(i * inv == BIG.new(1), 'Error in mod_inverse (gcd based)')

-- test additive homomorphic property
m = { } -- m int mod order
M = { } -- mG
-- aggregation results
local r = BIG.new(0)
local R = ECP.infinity() 

for i=1,10,1 do
   m[i] = BIG.random()
   r = r + m[i]
   M[i] = m[i] * g1
   R = R + M[i]
end
assert(R == r*g1, "Error in additive homomorphic property")


-- test zero-knowledge proof
wk = BIG.random()
k = BIG.random()
c = BIG.random()
rk = wk - c * k
-- rk = (wk - c*k) % o -- error when not using modsub
Aw1 = g1 * wk
Aw2 = (g1*k) * c + g1 * rk

assert(Aw1 == Aw2, 'Error in zero-knowledge proof')


print "OK"
print''
