# Noah_A__Kasper_Ncurses

A text encryption/decryption application with an ncurses-based user interface.

## Features

- Interactive terminal-based UI using ncurses
- Caesar cipher encryption and decryption
- Easy-to-use menu navigation with arrow keys
- Support for custom shift values (1-25)
- Colorful interface with visual feedback

## Requirements

- GCC compiler
- ncurses library (`libncurses-dev` on Debian/Ubuntu)
- Make

## Installation

### On Debian/Ubuntu:
```bash
sudo apt-get install gcc make libncurses-dev
```

### Build the application:
```bash
make
```

## Usage

Run the application:
```bash
./encrypt_app
```

Or use the make target:
```bash
make run
```

### Navigation

- Use **Arrow Keys** (Up/Down) to navigate the menu
- Press **Enter** to select an option
- Follow the on-screen prompts to enter text and shift values

### Menu Options

1. **Encrypt Text**: Enter text to encrypt and specify a shift value
2. **Decrypt Text**: Enter encrypted text and the same shift value to decrypt
3. **Exit**: Close the application

### Encryption Method

This application uses the Caesar cipher, a simple substitution cipher where each letter is shifted by a fixed number of positions in the alphabet. For example, with a shift of 3:
- A → D
- B → E
- Hello → Khoor

To decrypt, use the same shift value that was used for encryption.

## Example

1. Select "Encrypt Text"
2. Enter: `Hello World`
3. Enter shift value: `3`
4. Result: `Khoor Zruog`

Then to decrypt:
1. Select "Decrypt Text"
2. Enter: `Khoor Zruog`
3. Enter shift value: `3`
4. Result: `Hello World`

## Cleaning

To remove the compiled binary:
```bash
make clean
```

## License

This project is open source and available for educational purposes.
