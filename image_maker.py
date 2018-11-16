f = open("ccc.out","r")
cv = f.readline()
n,m = cv.split();
n = int(n)
m = int(m)

from PIL import Image
img = Image.new( '1', (n,m), "black") # Create a new black image
pixels = img.load() # Create the pixel map
for i in range(img.size[0]):    # For every pixel:
	a = str(f.readline())
	for j in range(img.size[1]):
		pixels[i,j] = (int(a[j]) * 255) # Set the colour accordingly

img.show()


