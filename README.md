<div align="center">
  <h1>🚀 C++ E-Commerce Management System</h1>
  <p>A high-performance CLI application for managing products, shopping carts, and orders with role-based access control.</p>

  <!-- Badges -->
  ![License](https://img.shields.io/badge/license-MIT-blue.svg)
  ![Version](https://img.shields.io/badge/version-1.0.0-green.svg)
  ![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
  ![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg)
</div>

---

## 📖 Table of Contents
- [About](#about)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)
- [Authors](#authors)

---

## 🎯 About
This project is a comprehensive **E-Commerce Management System** built in C++. It solves the problem of local inventory and order management for small businesses. It provides a dual-interface experience:
- **Admin Interface**: For managing the product catalog (Inventory CRUD).
- **Client Interface**: For a seamless shopping experience, including cart management and order validation.

The system handles data persistence using local text files, ensuring that your inventory and order history are preserved across sessions.

---

## ✨ Features
- 🔒 **Role-Based Authentication** — Secure login system with dedicated dashboards for Admins and Clients.
- 📦 **Inventory Management** — Full CRUD operations (Create, Read, Update, Delete) for products, including reference tracking.
- 🛒 **Advanced Shopping Cart** — Add articles, modify quantities, and automatic price recalculation.
- 💰 **Smart Discount System** — Built-in logic to apply a 20% discount automatically for bulk purchases (quantities > 10).
- 📜 **Order Processing** — Validate carts into formal orders with status tracking ("En cours", etc.).
- 💾 **Data Persistence** — Automatic saving and loading of the product catalog from `article.txt`.
- 🔍 **Advanced Filtering** — Search products by reference, price range, or find the most expensive item in your cart.

---

## 🛠️ Tech Stack
| Technology | Purpose |
|------------|---------|
| C++ (C++17) | Core Programming Language |
| STL | Data structures (list, vector, unordered_map) and algorithms |
| File I/O | Data persistence (fstream, sstream) |
| VS Code | Recommended Development Environment |

---

## 📦 Installation

### Prerequisites
- A C++ compiler (GCC/G++, Clang, or MSVC).
- Git (optional).

### Setup Steps
1. **Clone the repository**:
   ```bash
   git clone https://github.com/KhairatMouhcine/Projet_ecommerce.git
   cd Projet_ecommerce
   ```

2. **Compile the project**:
   Using G++:
   ```bash
   g++ produit.cpp -o ecommerce_app
   ```

3. **Run the application**:
   ```bash
   ./ecommerce_app
   ```

---

## 🚀 Usage

### 🔑 Default Credentials
| Role | Email | Password |
|------|-------|----------|
| Admin | b | b |
| Client | a | a |

### 📋 Main Menu Options
Upon login, you will be presented with a menu based on your role:
- **Client**: List products, manage cart, view total with discounts, and validate orders.
- **Admin**: Add new articles, update stock/prices, search by reference, and delete products.

---

## 📁 Project Structure
```text
Projet_ecommerce/
├── .vscode/               # VS Code configuration (debug & build tasks)
├── build/                 # Compiled binaries and object files
├── Dossier/               # Data storage directory
│   ├── article.txt        # Product database (Text format)
│   └── commandes.json     # Order history schema
├── pp.txt                 # Development notes and code snippets
├── produit.cpp            # Main source code (Logic, Classes, and UI)
└── README.md              # Project documentation
```


## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

---

## 👨‍💻 Authors

<table align="center">
  <tr>
    <td align="center">
      <img src="https://avatars.githubusercontent.com/KhairatMouhcine?v=4" width="100px" style="border-radius: 50%;" /><br />
      <sub><b>KhairatMouhcine</b></sub><br />
      <a href="https://github.com/KhairatMouhcine">
        <img src="https://img.shields.io/badge/GitHub-KhairatMouhcine-black?style=flat&logo=github" />
      </a><br />
      <a href="mailto:khairatmouhcine125@gmail.com">
        <img src="https://img.shields.io/badge/Email-khairatmouhcine125-red?style=flat&logo=gmail" />
      </a>
    </td>
    <td align="center">
      <img src="https://avatars.githubusercontent.com/Bassma02?v=4" width="100px" style="border-radius: 50%;" /><br />
      <sub><b>Bassma02</b></sub><br />
      <a href="https://github.com/Bassma02">
        <img src="https://img.shields.io/badge/GitHub-Bassma02-black?style=flat&logo=github" />
      </a><br />
      <a href="mailto:b.chihab2002@gmail.com">
        <img src="https://img.shields.io/badge/Email-b.chihab2002-red?style=flat&logo=gmail" />
      </a>
    </td>
  </tr>
</table>
