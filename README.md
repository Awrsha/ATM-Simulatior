# ATM Simulator with C++ and SFML Graphics Library

This is a simple ATM simulator program written in C++ language. The program allows the user to simulate ATM operations such as withdrawing money, depositing money, and transferring money between accounts. The program also includes a user login system and error handling for invalid inputs.

## SFML
SFML (Simple and Fast Multimedia Library) Graphics is a cross-platform multimedia library designed to provide a simple interface to various multimedia components such as graphics, audio, networking, and windowing system. It is written in C++ language and supports multiple programming languages including C, Python, and Java.

SFML Graphics provides a powerful set of features for 2D graphics rendering. Its API is object-oriented and designed to be simple and intuitive, making it easy to create complex graphics applications with minimal effort. Some of the features provided by SFML Graphics include:

- Support for hardware-accelerated graphics rendering using OpenGL and Direct3D.
- Support for multiple window creation and management.
- Support for loading and displaying various image formats such as PNG, JPEG, and BMP.
- Support for drawing 2D shapes such as points, lines, rectangles, circles, and polygons.
- Support for text rendering and manipulation.
- Support for sprite sheets, animations, and transformations.
- Support for shader programs to create advanced graphics effects.

SFML Graphics is widely used in the game development industry due to its simplicity and performance. It is also used in other graphics-intensive applications such as simulations, visualizations, and user interfaces.
## Requirements

To run this program, you will need:
- C++ compiler
- SFML Graphics Library

## Installation

### Installing SFML Graphics Library

1. Download the SFML library from the official website: [https://www.sfml-dev.org/download.php ↗](https://www.sfml-dev.org/download.php)
2. Extract the downloaded file to a directory of your choice.
3. Add the SFML library to your C++ project by following these steps:
   - Open your IDE or text editor and create a new C++ project.
   - Add the path to the SFML library include files to your project's include path.
   - Add the path to the SFML library object files to your project's linker path.
   - Link your project against the SFML library by adding the appropriate linker flags.

### Compiling and Running the Program

1. Clone or download the source code from this repository.
2. Open a terminal or command prompt and navigate to the project directory.
3. Use the following command to compile the program:
   ````
   g++ -o atm main.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ````

4. Use the following command to run the program:
   ````
   ./atm
   ````

## Usage

When you run the program, you will be prompted to enter your account number and PIN. If you do not have an account, you can create a new account by selecting the "Create Account" option from the main menu.

Once you have logged in, you can select from the following options:
- Check Balance: View the balance of your account.
- Deposit: Add money to your account.
- Withdraw: Withdraw money from your account.
- Transfer: Transfer money from your account to another account.

After completing your transaction, you will be returned to the main menu.

## Contributing

This is an open-source project and contributions are welcome. To contribute, please fork this repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
