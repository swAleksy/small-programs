import pytesseract as pyt
import cv2
import pdf2image
import numpy as np
from PyPDF2 import PdfMerger
import os
import tempfile

double_scaned = 0

poppler_path = "path_to_poppler" #poppler-24.07.0/Library/bin
pdf_path = "path_to_pdf"

print("000")
pages = pdf2image.convert_from_path(pdf_path=pdf_path, poppler_path=poppler_path)
print("00")
pyt.pytesseract.tesseract_cmd = "path_to_tesseract"
print("0")
i = 0
pages_to_conv = []
for page in pages:
    image = cv2.cvtColor(np.array(page), cv2.COLOR_RGB2BGR)
    print("1")
    if double_scaned:
        height, width, _ = image.shape

        middle = width // 2
        left_half = image[:, :middle] 
        right_half = image[:, middle:]

        pages_to_conv.append(left_half)
        pages_to_conv.append(right_half)
    else:
        pages_to_conv.append(image)

    i += 1
print("2")
x = []
merger = PdfMerger()

with tempfile.TemporaryDirectory() as tempdir:
    print("3")
    temp_files = []
    
    for idx, img in enumerate(pages_to_conv):
        print(idx)

        pdf_data = pyt.image_to_pdf_or_hocr(img, extension='pdf')
        temp_pdf_path = os.path.join(tempdir, f"temp_page_{idx}.pdf")
        
        with open(temp_pdf_path, 'wb') as temp_pdf_file:
            temp_pdf_file.write(pdf_data)

        temp_files.append(temp_pdf_path)


    for temp_file in temp_files:
        with open(temp_file, 'rb') as f:
            merger.append(f)

    with open("result.pdf", "wb") as f:
        merger.write(f)
