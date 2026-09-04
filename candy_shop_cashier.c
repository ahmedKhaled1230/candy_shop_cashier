#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CANDY_KINDS   6U
#define BASKET_MAX    8U
#define NAME_LEN     16U

typedef struct {
    char     name[NAME_LEN];
    uint16_t price;
    uint16_t stock;
    uint16_t sold;
} Candy_t;

typedef struct {
    uint8_t  candyId;
    uint8_t  qty;
} Line_t;

static Candy_t shelf[CANDY_KINDS];
static Line_t  basket[BASKET_MAX];
static uint8_t basketLines;
static uint32_t cashDrawer;


static void     openShop(void);
static void     showShelf(void);
static void     addToBasket(void);
static void     removeFromBasket(void);
static uint32_t basketTotal(void);
static void     showBasket(void);
static void     checkout(void);
static void     giveChange(uint32_t change);
static uint8_t  bestSeller(void);
static void     dayReport(void);

int main(void) {
    openShop();
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show shelf\n");
        printf("2. Add to basket\n");
        printf("3. Remove from basket\n");
        printf("4. Show basket\n");
        printf("5. Checkout\n");
        printf("6. Day report\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 0;
        }
        switch (choice) {
            case 1: showShelf(); break;
            case 2: addToBasket(); break;
            case 3: removeFromBasket(); break;
            case 4: showBasket(); break;
            case 5: checkout(); break;
            case 6: dayReport(); break;
            case 0: break;
            default: printf("Unknown option!\n"); break;
        }
    } while (choice != 0);
    return 0;
}


static void openShop(void) {
    const char *names[CANDY_KINDS] = {"Lollipop","Chocolate","Gum","Caramel","Marshmallow","Cookie"};
    const uint16_t prices[CANDY_KINDS] = {50, 200, 25, 100, 150, 75};
    const uint16_t stocks[CANDY_KINDS] = {20, 10, 30, 15, 25, 12};
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        strncpy(shelf[i].name, names[i], NAME_LEN);
        shelf[i].price = prices[i];
        shelf[i].stock = stocks[i];
        shelf[i].sold = 0;
    }
    basketLines = 0;
    cashDrawer = 0;
}

static void showShelf(void) {
    printf("\nShelf:\n");
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        printf("%u: %-12s %3u piastres | %s\n",
               i, shelf[i].name, shelf[i].price,
               (shelf[i].stock == 0) ? "SOLD OUT" : "");
        if (shelf[i].stock > 0) {
            printf("   Stock: %u\n", shelf[i].stock);
        }
    }
}

static void addToBasket(void) {
    int id, qty;
    printf("Which candy (0-5)? ");
    if (scanf("%d", &id) != 1 || id < 0 || id >= (int)CANDY_KINDS) {
        printf("Invalid candy!\n");
        return;
    }
    printf("How many? ");
    if (scanf("%d", &qty) != 1 || qty <= 0 || qty > UINT8_MAX) {
        printf("Invalid number!\n");
        return;
    }
    if (shelf[id].stock < qty) {
        printf("Not enough stock!\n");
        return;
    }
    for (uint8_t i = 0; i < basketLines; i++) {
        if (basket[i].candyId == id) {
            basket[i].qty += qty;
            return;
        }
    }
    if (basketLines >= BASKET_MAX) {
        printf("Basket full!\n");
        return;
    }
    basket[basketLines].candyId = (uint8_t)id;
    basket[basketLines].qty = (uint8_t)qty;
    basketLines++;
}

static void removeFromBasket(void) {
    int line;
    if (basketLines == 0) {
        printf("Basket is empty!\n");
        return;
    }
    printf("Which basket line (0-%u)? ", (unsigned)(basketLines - 1U));
    if (scanf("%d", &line) != 1 || line < 0 || line >= basketLines) {
        printf("Invalid line!\n");
        return;
    }
    for (uint8_t i = line; i < basketLines-1; i++) {
        basket[i] = basket[i+1];
    }
    basketLines--;
}

static uint32_t basketTotal(void) {
    uint32_t total = 0;
    for (uint8_t i = 0; i < basketLines; i++) {
        total += basket[i].qty * shelf[basket[i].candyId].price;
    }
    return total;
}

static void showBasket(void) {
    printf("\nBasket:\n");
    for (uint8_t i = 0; i < basketLines; i++) {
        Candy_t *c = &shelf[basket[i].candyId];
        uint32_t lineCost = basket[i].qty * c->price;
        printf("%s x%u @%u = %u\n", c->name, basket[i].qty, c->price, lineCost);
    }
    printf("Total: %u\n", basketTotal());
}

static void checkout(void) {
    uint32_t total = basketTotal();
    printf("Total: %u\n", total);
    int money;
    printf("Money given: ");
    if (scanf("%d", &money) != 1 || money < 0) {
        printf("Invalid input!\n");
        return;
    }
    if ((uint32_t)money < total) {
        printf("Not enough money!\n");
        return;
    }
    for (uint8_t i = 0; i < basketLines; i++) {
        shelf[basket[i].candyId].stock -= basket[i].qty;
        shelf[basket[i].candyId].sold += basket[i].qty;
    }
    cashDrawer += total;
    giveChange((uint32_t)money - total);
    basketLines = 0;
}

static void giveChange(uint32_t change) {
    if (change == 0) {
        printf("No change, thank you!\n");
        return;
    }
    uint16_t coins[5] = {500,200,100,50,25};
    for (uint8_t i = 0; i < 5; i++) {
        uint32_t count = change / coins[i];
        if (count > 0) {
            printf("%u x %u\n", coins[i], count);
            change -= count * coins[i];
        }
    }
    if (change > 0) {
        printf("Cannot return exact change, leftover: %u\n", change);
    }
}

static uint8_t bestSeller(void) {
    uint8_t pos = 0;
    for (uint8_t i = 1; i < CANDY_KINDS; i++) {
        if (shelf[i].sold > shelf[pos].sold) {
            pos = i;
        }
    }
    return pos;
}

static void dayReport(void) {
    printf("\nDay Report:\n");
    printf("Cash drawer: %u\n", cashDrawer);
    uint32_t totalSold = 0;
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        totalSold += shelf[i].sold;
    }
    printf("Candies sold: %u\n", totalSold);
    uint8_t best = bestSeller();
    printf("Best seller: %s\n", shelf[best].name);
    printf("Sold out:\n");
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        if (shelf[i].stock == 0) {
            printf(" - %s\n", shelf[i].name);
        }
    }
}