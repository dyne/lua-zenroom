O = require'octet'
ECDH = require'ecdh'

print("TEST VECTORS from IEEE802 (RANDALL)")
-- http://www.ieee802.org/1/files/public/docs2011/bn-randall-test-vectors-0511-v1.pdf

print('60-Byte Packet Encryption Using GCM-AES-128')
key = O.from_hex('AD7A2BD03EAC835A6F620FDCB506B345')
iv = O.from_hex('12153524C0895E81B2C28465')
header = O.from_hex('D609B1F056637A0D46DF998D88E52E00B2C2846512153524C0895E81')
plain = O.from_hex('08000F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A0002')

encoded, chksum = ECDH.aead_encrypt(key, plain, iv, header)

assert( O.from_hex('701AFA1CC039C0D765128A665DAB69243899BF7318CCDC81C9931DA17FBE8EDD7D17CB8B4C26FC81E3284F2B7FBA713D') == encoded and O.from_hex('4F8D55E7D3F06FD5A13C0C29B9D5B880') == chksum, "60-Byte Packet Encryption Using GCM-AES-128 FAILED")


print('60-byte Packet Encryption Using GCM-AES-256')
key = O.from_hex('E3C08A8F06C6E3AD95A70557B23F75483CE33021A9C72B7025666204C69C0B72')
plain = O.from_hex('08000F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A0002')
header = O.from_hex('D609B1F056637A0D46DF998D88E52E00B2C2846512153524C0895E81')
iv = O.from_hex('12153524C0895E81B2C28465')

encoded, chksum = ECDH.aead_encrypt(key, plain, iv, header)

assert( O.from_hex('E2006EB42F5277022D9B19925BC419D7A592666C925FE2EF718EB4E308EFEAA7C5273B394118860A5BE2A97F56AB7836') == encoded and O.from_hex('5CA597CDBB3EDB8D1A1151EA0AF7B436') == chksum, "60-byte Packet Encryption Using GCM-AES-256 FAILED")

-- TODO: complete with other tests from PDF
