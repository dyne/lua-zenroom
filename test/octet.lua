print '= OCTET FIRST CLASS CITIZEN TESTS'
print()

OCTET = require'octet'

function dotest(l,r,reason)
   if(l == r
	  and
	  #l == #r) then
	  return true
   else
	  print 'ERROR'
	  print 'left:'
	  print(l)
	  print 'right:'
	  print(r)
	  assert(false, reason)
   end
end

-- random and  check hash of octets
-- ecdh = require'ecdh'
right = OCTET.string([[Minim quis typewriter ut. Deep v ut man braid neutra culpa in officia consectetur tousled art party stumptown yuccie. Elit lo-fi pour-over woke venmo keffiyeh in normcore enim sunt labore williamsburg flexitarian. Tumblr distillery fanny pack, banjo tacos vaporware keffiyeh.]])
teststr = right:string()
test64  = right:base64()
testU64 = right:url64()
test58  = right:base58()
testhex = right:hex()
testbin = right:bin()

print '== test octet copy'
left = right;
dotest(left, right)

print '== test string import/export'
left = OCTET.string(teststr)
print '=== compare octets'
dotest(left, right)
print '=== compare strings'
dotest(left:string(), teststr)

print '== test base64 import/export'
left = OCTET.base64(test64)
dotest(left, right)
dotest(left:base64(), test64)

print '== test url64 import/export'
left = OCTET.url64(testU64)
dotest(left, right)
dotest(left:url64(), testU64)

print '== test base58 import/export'
left = OCTET.base58(test58)
dotest(left, right)
dotest(left:base58(), test58)


print '== test hex import/export'
left = OCTET.hex(testhex)
dotest(left, right)
dotest(left:hex(), testhex)

print '== test bin import/export'
left = OCTET.bin(testbin)
dotest(left, right)
dotest(left:bin(), testbin)

-- print '= OK'

print '== random import/export'

left = OCTET.random(64)
b64 = left:octet():base64()
right = OCTET.from_base64(b64)
dotest(left:octet(),right)



print '= OK'
