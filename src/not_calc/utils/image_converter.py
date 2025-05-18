from PIL import Image

image = Image.open("hat.png")
pixels = image.load()

width, height = image.size

print("{\n    ", end="")
for y in range(height):
    for x in range(width):
        r, g, b, p = image.getpixel((x, y))
        h = hex(r*65536 + g*256 + b*1)
        print(f"Color({h}), ", end="")
    print("\n    ", end="")
print("\n}")
