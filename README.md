# 📊 Daily Sales Management System (Warung Version)

This project is a **C++-based daily sales recording system** designed for small stores (known as *warungs* in Indonesia). It helps users track daily sales, manage product data, calculate net savings, and navigate through daily transactions.

## 🚀 Features

- **Daily Sales Input**  
  Record product sales for each day with quantity and price.

- **Daily & Monthly Sales History**  
  View sales by specific date or summarized monthly performance.

- **Net Savings Calculation**  
  Calculates clean savings = total monthly income - monthly capital.

- **Simple Calendar Navigation**  
  Supports day increments and date changes, including leap year adjustments.

- **Product Categorization**  
  Products are grouped into:
  - Basic Needs (Sembako)
  - Medicines
  - Snacks & Drinks
  - Household Tools

## 📁 Data Structures

- `Produk`  
  Stores product name, price, and category.

- `DetailPenjualan`  
  Stores product name, price per item, and quantity sold.

- `PenjualanHarian`  
  Holds daily total sales and a list of sold product details.

- `PenjualanHarian[12][31]`  
  A 2D array that stores data per **month (0–11)** and **day (0–30)**.

## 🗓️ Calendar Logic

- Day/month auto-increment with overflow check
- February includes leap year detection
- Manual date changes are supported

## 💰 Financial Summary

- **Total Daily Sales** = Sum of (product price × quantity)  
- **Net Monthly Savings** = Monthly Sales Total − Monthly Capital

## ▶️ How to Run

1. Compile the program using your favorite C++ compiler (e.g., `g++ main.cpp -o app`).
2. Run the executable (`./app`).
3. Input initial date and monthly capital.
4. Use the main menu to:
   - Record sales
   - View reports
   - Navigate calendar
   - Exit program

## ⚠️ Notes

- **No persistent storage yet**. Data is stored in memory only and will be lost upon program exit.
- Designed for educational and small business use.
- Does **not** use any external libraries — just standard C++.

## ✅ Future Improvements

- Persistent storage with file read/write
- Export reports to `.txt` or `.csv`
- Product inventory system
- Profit/loss graphs with external library (e.g., SFML)

## 👨‍💻 Author

- **Name:** [Falih Elmanda]  
- **GitHub:** [Elmanda1]  
- **Date:** November 2024  
- **Language:** C++

---

**Made with ❤️ for small businesses and learners**

