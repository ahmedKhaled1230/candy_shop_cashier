# Candy Shop Cashier

## Author

- Name: Ahmed Khaled Mohamed Youssri Khaled Elbohy
- Email: ahmed2006688@gmail.com

## Overview

This is a plain C99 console cashier for a small candy shop. It supports:

- Viewing six candies and their remaining stock
- Adding and removing candy from a basket
- Combining repeated additions of the same candy into one basket line
- Calculating a basket total and checking out
- Returning change with the available 500, 200, 100, 50, and 25 piastre coins
- Reporting cash received, total candies sold, the best seller, and sold-out items

## Build and run

Using GCC:

```text
gcc -std=c99 -Wall -Wextra -Wpedantic candy_shop_cashier.c -o candy_shop_cashier
./candy_shop_cashier
```

On Windows, run `candy_shop_cashier.exe` after compilation.

## Input behavior

Invalid menu, candy, quantity, basket-line, and payment values are rejected. A
quantity must be positive and fit in the basket quantity field. An underpaid
purchase leaves the basket and stock unchanged. Stock is reduced only after
successful payment.

## Change limitation

The available denominations are 500, 200, 100, 50, and 25 piastres. They can
only make multiples of 25, so exact change for 137 piastres is impossible. The
program returns the largest representable part using the available coins and
reports the leftover amount. The sale still completes because the cashier has
accepted the payment; the leftover must be handled manually.

## Source brief

The implementation follows Project 3, “Candy Shop Cashier,” from
`Five_C_Practice_Projects (1).md`. All project functions are `static`, and the
program uses only the standard C headers requested by the brief.