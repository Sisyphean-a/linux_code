import cv2
imge=cv2.imread('1.jpg')
imge=cv2.resize(imge,(1366,768))
#print(imge)
cv2.imshow('image',imge)
cv2.waitKey(0)