from PIL import Image

def rgb2hsl(r,g,b,a):
    r /= 255
    g /= 255
    b /= 255
    M = max(r, g, b)
    m = min(r, g, b)
    l = M
    if M==m:
        h = 0
        s = 0
    else:
        d = M-m
        s = d/l
        if M==r:
            if g<b: h = (g-b)/d+6
            else: h = (g-b)/d
        if M==g: h = (b-r)/d+2
        if M==b: h = (r-g)/d+4
    h /= 6
    h = int(h*255)
    s = int(s*255)
    l = int(l*255)
    return (h,s,l,a)

im = Image.open('pic2_rgb.png')
pix = im.load()
print(im.size)
for x in range(im.size[0]):
    for y in range(im.size[1]):
        pix[x,y] = rgb2hsl(pix[x,y][0], pix[x,y][1], pix[x,y][2], pix[x,y][3])
im.save('pic2_hsl.png')
