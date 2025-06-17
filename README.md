# 📌 DCT-Based Image Steganography in C

This project demonstrates how to **hide (encode)** and **retrieve (decode)** a secret message inside a grayscale BMP image using the **Discrete Cosine Transform (DCT)**. It modifies certain frequency coefficients to embed bits of your message without making visible changes to the image.

---

## 🖼 Example BMP used

👉 `lena_gray.bmp` — A 256x256 grayscale BMP image (8-bit, 1078-byte header).

---

## ⚙ Project Structure

dct-stegnography-c/
├── main.c # Main code: handles I/O, encode & decode
├── dct.c # DCT and inverse DCT calculations
├── dct.h # Header file for DCT functions
├── lena_gray.bmp # Cover image (must be 256x256 grayscale BMP)
├── secret.txt # Your secret message
├── run_stego.bat # Windows batch file to compile + run
├── stego.bmp # Output image with hidden message (generated)


---

## 🚀 How it works

✅ **Encoding**
- The image is processed in 8×8 blocks.
- DCT is applied to each block.
- A bit of the message is embedded into the least significant bit of the coefficient at position `[4][3]`.
- Inverse DCT reconstructs the image block.
- The modified image is saved as `stego.bmp`.

✅ **Decoding**
- Reads `stego.bmp`.
- Applies DCT to each 8×8 block.
- Extracts LSB of `[4][3]` and reconstructs the message bit-by-bit.
- Stops when the null terminator (`\0`) is found.

---

## 📦 How to set up

### 1️⃣ Prerequisites
- Install [MinGW](http://www.mingw.org/) (for `gcc` on Windows)
- Add `gcc` to your system PATH

### 2️⃣ Files you need
- Download/save the files:
  - `main.c`
  - `dct.c`
  - `dct.h`
  - `lena_gray.bmp` (must be 256x256 grayscale BMP)
  - `secret.txt` (add your message here)
  - `run_stego.bat`

---

## 💻 How to compile & run

### Option A — Use the batch file (recommended on Windows)

1️⃣ Open **PowerShell** or **Command Prompt**  
2️⃣ Navigate to project folder:
cd "C:\Users\YourName\Path\To\dct-stegnography-c"

### 3️⃣ Run:

run_stego.bat

It will compile and run stego.exe.

### Option B — Manually compile & run

1️⃣ Open **PowerShell** or **Command Prompt**
2️⃣ Navigate to project folder:
cd "C:\Users\YourName\Path\To\dct-stegnography-c"
### 3️⃣ Compile:
gcc main.c dct.c -o stego.exe

🔑 Notes
✅ The image must be:

256x256

8-bit grayscale BMP

With 1078-byte header (54 bytes + 1024 palette)

✅ secret.txt should have your message.
✅ The message is null-terminated (\0) to mark end during decode.

⚡ Limitations
⚠ The size of your message is limited by how many 8×8 blocks fit in the image:

256×256 → 1024 blocks → max ~1024 characters (1 char = 8 bits, 1 block = 1 bit)

🧠 What you’ll learn
DCT and IDCT implementation

Basic image processing

LSB steganography in frequency domain

Handling BMP file formats

💡 Possible improvements
Use multiple coefficients or bits per block

Add encryption to the message before embedding

Support color BMP (RGB)

Use other frequency domain techniques (e.g. DWT)

🤝 Credits
Inspired by JPEG compression DCT concept.