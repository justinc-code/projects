import os, sys, warnings, timeit

from PIL import Image
import numpy as np

# Initializes the color's center of the image
def initialize_color_center(image_pixels, color_clarity):

    # Takes random index from row and determines if the color clarity is to be replaced
    return image_pixels[np.random.choice(len(image_pixels), color_clarity, replace=False),:]

# Finds closest center of image and returns index of closest center for the image in an m-dimensional vector
def find_closest_center(image_pixels, center):
    image_length = len(image_pixels)
    center_vector = np.zeros(image_length)
    
    for i in range(center_vector):
        distances = np.linalg.norm(image_pixels[i] - center, axis=1)
        center_vector = np.argmin(distances)
        
    return center_vector

# Find means of the image's pixels
def compute_means(image_pixels, close_center, color_clarity):
    _, n = image_pixels.shape
    center = np.zeros((color_clarity, n))
    for j in range(color_clarity):
    
        with warnings.catch_warnings():
            warnings.filterwarnings("error")
            try:
                image = image_pixels[np.where(close_center==j)]
                mean = [np.mean(column) for column in image.T]
                center[j] = mean
            except RuntimeWarning:
                mean = np.NaN
    return center

# Calculates the average color within the image's pixels
def find_color_average(image_pixels, color_clarity, max_iters=1):
    center = initialize_color_center(image_pixels, color_clarity)
    previous_cetner = center
    
    for _ in range(max_iters):
        close_center = find_closest_center(image_pixels, center)
        center = compute_means(image_pixels, close_center, color_clarity)
        
        if(center == previous_center).all():
            return center
            
        else:
            previous_center = center
            
    return center, close_center

# Loads the image
def load_image(path):
    image = Image.open(path)
    return np.asarray(image)/255

if __name__ == '__main__':
    # Loads the image using a direct path to the picture.
    image = load_image(r"C:\\Users\\Justin\\Desktop\\test_image.jpeg")
    # Gets the image's dimension and sets it to the width, height, and depth
    width, height, depth = image.shape

    image_pixels = image.reshape((width*height, depth))
    
    # Amount of colors in the compressed picture
    color_clarity = 40

    print("Running: Finding Average Pixel Color")
    time0 = timeit.default_timer()
    colors, _ = find_color_average(image_pixels, color_clarity, max_iters = 1)

    time1 = timeit.default_timer()

    if (time1-time0) > 60: 
        print("Calculating Average Pixel Color Took: %0.2f minutes" % ((time1-time0) / 60))
    else:
        print("Calculating Average Pixel Color Took: %0.2f seconds" % (time1-time0))

    
    close_center = find_closest_center(image_pixels, colors)
    print("Taking Array and Converting to An Image")

    close_center = np.array(close_center, dtype = np.uint8)
    
    image_reconstructed = np.array(colors[close_center, :]*255, dtype=np.uint8).reshape((width, height, depth))
    compressed_image = Image.fromarray(image_reconstructed)

    compressed_image.save("compressed_image.jpeg")
    
    time5 = timeit.default_timer()
    if (time5-time0) > 60:
        print("DONE: Total Runtime is %0.2f minutes" % ((time5-time0) / 60))
    else:
        print("DONE: Total Runtime is %0.2f seconds" %(time5-time0))