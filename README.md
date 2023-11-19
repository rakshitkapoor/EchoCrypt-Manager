# EchoCrypt-Manager
Encryption and decryption Password manager 
Description:
EchoCrypt-Manager is a C++ project that implements a secure and robust password management system using the RSA algorithm for encryption. The project provides a command-line interface for users to interact with, enabling them to securely store, retrieve, and manage their passwords. The RSA algorithm is employed to ensure the confidentiality and integrity of stored passwords, making the system resilient against unauthorized access.

# Key Features:

RSA Encryption: Utilizes the RSA algorithm for secure password encryption, incorporating keys (e, d, n) to safeguard user credentials.
Struct-Based Data Management: Employs C++ structs to encapsulate and manage password-related data, enhancing modularity and readability.
File Handling: Implements file handling for persistent storage of encrypted passwords, allowing users to save and retrieve their credentials securely.
User-Friendly Interface: Provides an intuitive command-line interface with options for entering, finding, and deleting passwords.

# How to Use:

Enter a Password: Allows users to input website details, usernames, and passwords, encrypting them securely with RSA.

Find Password: Enables users to retrieve decrypted passwords by entering the website and username details.

Delete Password: Provides an option to delete stored passwords based on website and username.

Save & Exit: Persists the encrypted password data to a file, ensuring data persistence across sessions.

# Dependencies:

C++ Compiler
