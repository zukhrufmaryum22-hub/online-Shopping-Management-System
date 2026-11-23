
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Product
{
    int productID;
    string productName;
    string category;
    double price;
    int stock;
};

struct ProductNode
{
    Product data;
    ProductNode* next;
};

struct CartNode
{
    int productID;
    int quantity;
    CartNode* next;
};

struct Order
{
    int orderID;
    string customerName;
    int productID;
    string productName;
    int quantity;
    double price;
    double totalAmount;
};

struct OrderNode
{
    Order data;
    OrderNode* next;
};

ProductNode* productHead = NULL;
CartNode* cartTop = NULL;
OrderNode* front = NULL;
OrderNode* rear = NULL;

int nextOrderID = 1001;

// --------------------------------------------------
// PRODUCT SEARCH BY ID
// --------------------------------------------------

ProductNode* findProduct(int id)
{
    ProductNode* temp = productHead;

    while (temp != NULL)
    {
        if (temp->data.productID == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

// --------------------------------------------------
// ADD PRODUCT
// --------------------------------------------------

void addProduct()
{
    Product p;

    cout << "\nEnter Product ID: ";
    cin >> p.productID;

    if (findProduct(p.productID) != NULL)
    {
        cout << "\nDuplicate Product ID! Product not added.\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin.ignore(1000, '\n');
    getline(cin, p.productName);

    cout << "Enter Category: ";
    getline(cin, p.category);

    cout << "Enter Price: ";
    cin >> p.price;

    cout << "Enter Stock: ";
    cin >> p.stock;

    if (p.price <= 0 || p.stock < 0)
    {
        cout << "\nInvalid price or stock!\n";
        return;
    }

    ProductNode* newNode = new ProductNode;

    newNode->data = p;
    newNode->next = NULL;

    if (productHead == NULL)
    {
        productHead = newNode;
    }
    else
    {
        ProductNode* temp = productHead;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    cout << "\nProduct registered successfully!\n";
}

// --------------------------------------------------
// DISPLAY PRODUCTS
// --------------------------------------------------

void displayProducts()
{
    if (productHead == NULL)
    {
        cout << "\nNo products available!\n";
        return;
    }

    ProductNode* temp = productHead;

    cout << "\n========== PRODUCT INVENTORY ==========\n";

    while (temp != NULL)
    {
        cout << "\nProduct ID: " << temp->data.productID;
        cout << "\nName: " << temp->data.productName;
        cout << "\nCategory: " << temp->data.category;
        cout << "\nPrice: " << temp->data.price;
        cout << "\nAvailable Stock: " << temp->data.stock;
        cout << "\n---------------------------------------\n";

        temp = temp->next;
    }
}

// --------------------------------------------------
// UPDATE PRODUCT
// --------------------------------------------------

void updateProduct()
{
    int id;

    cout << "\nEnter Product ID to update: ";
    cin >> id;

    ProductNode* temp = findProduct(id);

    if (temp == NULL)
    {
        cout << "\nProduct not found!\n";
        return;
    }

    cout << "\nEnter New Product Name: ";
    cin.ignore(1000, '\n');
    getline(cin, temp->data.productName);

    cout << "Enter New Category: ";
    getline(cin, temp->data.category);

    double newPrice;
    int newStock;

    cout << "Enter New Price: ";
    cin >> newPrice;

    cout << "Enter New Stock: ";
    cin >> newStock;

    if (newPrice <= 0 || newStock < 0)
    {
        cout << "\nInvalid price or stock! Update cancelled.\n";
        return;
    }

    temp->data.price = newPrice;
    temp->data.stock = newStock;

    cout << "\nProduct updated successfully!\n";
}

// --------------------------------------------------
// DELETE PRODUCT
// --------------------------------------------------

void deleteProduct()
{
    int id;

    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    ProductNode* temp = productHead;
    ProductNode* previous = NULL;

    while (temp != NULL && temp->data.productID != id)
    {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "\nProduct not found!\n";
        return;
    }

    // Do not delete a product already in the cart
    CartNode* cartTemp = cartTop;

    while (cartTemp != NULL)
    {
        if (cartTemp->productID == id)
        {
            cout << "\nCannot delete! Product is in the shopping cart.\n";
            return;
        }

        cartTemp = cartTemp->next;
    }

    if (previous == NULL)
        productHead = temp->next;
    else
        previous->next = temp->next;

    delete temp;

    cout << "\nProduct deleted successfully!\n";
}

// --------------------------------------------------
// SEARCH PRODUCTS
// --------------------------------------------------

void searchProducts()
{
    int choice;

    cout << "\n========== SEARCH PRODUCTS ==========\n";
    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Category\n";
    cout << "4. Search by Price\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;

        ProductNode* temp = findProduct(id);

        if (temp == NULL)
        {
            cout << "\nProduct not found!\n";
            return;
        }

        cout << "\nProduct Found: "
             << temp->data.productName
             << " | Price: " << temp->data.price
             << " | Stock: " << temp->data.stock << endl;
    }
    else if (choice == 2 || choice == 3)
    {
        string value;
        bool found = false;

        cout << (choice == 2 ? "Enter Product Name: " : "Enter Category: ");
        cin.ignore(1000, '\n');
        getline(cin, value);

        ProductNode* temp = productHead;

        while (temp != NULL)
        {
            if ((choice == 2 && temp->data.productName == value) ||
                (choice == 3 && temp->data.category == value))
            {
                cout << "\nID: " << temp->data.productID
                     << " | Name: " << temp->data.productName
                     << " | Category: " << temp->data.category
                     << " | Price: " << temp->data.price
                     << " | Stock: " << temp->data.stock << endl;

                found = true;
            }

            temp = temp->next;
        }

        if (!found)
            cout << "\nProduct not found!\n";
    }
    else if (choice == 4)
    {
        double price;
        bool found = false;

        cout << "Enter exact product price: ";
        cin >> price;

        ProductNode* temp = productHead;

        while (temp != NULL)
        {
            if (temp->data.price == price)
            {
                cout << "\nID: " << temp->data.productID
                     << " | Name: " << temp->data.productName
                     << " | Price: " << temp->data.price << endl;

                found = true;
            }

            temp = temp->next;
        }

        if (!found)
            cout << "\nProduct not found!\n";
    }
    else
    {
        cout << "\nInvalid search choice!\n";
    }
}

// --------------------------------------------------
// BUBBLE SORT BY ID
// --------------------------------------------------

void sortByID()
{
    bool swapped;

    if (productHead == NULL)
        return;

    do
    {
        swapped = false;
        ProductNode* temp = productHead;

        while (temp->next != NULL)
        {
            if (temp->data.productID > temp->next->data.productID)
            {
                Product swapData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swapData;

                swapped = true;
            }

            temp = temp->next;
        }

    } while (swapped);

    cout << "\nProducts sorted by ID!\n";
}

// --------------------------------------------------
// BUBBLE SORT BY NAME
// --------------------------------------------------

void sortByName()
{
    bool swapped;

    if (productHead == NULL)
        return;

    do
    {
        swapped = false;
        ProductNode* temp = productHead;

        while (temp->next != NULL)
        {
            if (temp->data.productName > temp->next->data.productName)
            {
                Product swapData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swapData;

                swapped = true;
            }

            temp = temp->next;
        }

    } while (swapped);

    cout << "\nProducts sorted by Name!\n";
}

// --------------------------------------------------
// BUBBLE SORT BY CATEGORY
// --------------------------------------------------

void sortByCategory()
{
    bool swapped;

    if (productHead == NULL)
        return;

    do
    {
        swapped = false;
        ProductNode* temp = productHead;

        while (temp->next != NULL)
        {
            if (temp->data.category > temp->next->data.category)
            {
                Product swapData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swapData;

                swapped = true;
            }

            temp = temp->next;
        }

    } while (swapped);

    cout << "\nProducts sorted by Category!\n";
}

// --------------------------------------------------
// BUBBLE SORT BY PRICE
// --------------------------------------------------

void sortByPrice()
{
    bool swapped;

    if (productHead == NULL)
        return;

    do
    {
        swapped = false;
        ProductNode* temp = productHead;

        while (temp->next != NULL)
        {
            if (temp->data.price > temp->next->data.price)
            {
                Product swapData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swapData;

                swapped = true;
            }

            temp = temp->next;
        }

    } while (swapped);

    cout << "\nProducts sorted by Price!\n";
}

// --------------------------------------------------
// SORTING MENU
// --------------------------------------------------

void sortingMenu()
{
    int choice;

    cout << "\n========== SORT PRODUCTS ==========\n";
    cout << "1. Sort by ID\n";
    cout << "2. Sort by Name\n";
    cout << "3. Sort by Category\n";
    cout << "4. Sort by Price\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        sortByID();
        break;

    case 2:
        sortByName();
        break;

    case 3:
        sortByCategory();
        break;

    case 4:
        sortByPrice();
        break;

    default:
        cout << "\nInvalid sorting choice!\n";
        return;
    }

    displayProducts();
}

// --------------------------------------------------
// ADD PRODUCT TO STACK-BASED CART
// --------------------------------------------------

void addToCart()
{
    int id, quantity;

    cout << "\nEnter Product ID: ";
    cin >> id;

    ProductNode* product = findProduct(id);

    if (product == NULL)
    {
        cout << "\nProduct not available!\n";
        return;
    }

    cout << "Enter Quantity: ";
    cin >> quantity;

    if (quantity <= 0)
    {
        cout << "\nInvalid quantity!\n";
        return;
    }

    if (quantity > product->data.stock)
    {
        cout << "\nInsufficient stock!\n";
        return;
    }

    // Check total quantity already in cart for this product
    int existingQuantity = 0;
    CartNode* temp = cartTop;

    while (temp != NULL)
    {
        if (temp->productID == id)
            existingQuantity += temp->quantity;

        temp = temp->next;
    }

    if (existingQuantity + quantity > product->data.stock)
    {
        cout << "\nInsufficient stock for total cart quantity!\n";
        return;
    }

    CartNode* newNode = new CartNode;

    newNode->productID = id;
    newNode->quantity = quantity;
    newNode->next = cartTop;

    cartTop = newNode;

    cout << "\nProduct added to shopping cart!\n";
}

// --------------------------------------------------
// REMOVE LAST ADDED CART ITEM
// --------------------------------------------------

void removeFromCart()
{
    if (cartTop == NULL)
    {
        cout << "\nShopping Cart is Empty!\n";
        return;
    }

    CartNode* temp = cartTop;

    cout << "\nRemoved Product ID: "
         << temp->productID << endl;

    cartTop = cartTop->next;

    delete temp;
}

// --------------------------------------------------
// DISPLAY CART AND CALCULATE TOTAL
// --------------------------------------------------

double displayCart()
{
    if (cartTop == NULL)
    {
        cout << "\nShopping Cart is Empty!\n";
        return 0;
    }

    double total = 0;
    CartNode* temp = cartTop;

    cout << "\n========== SHOPPING CART ==========\n";

    while (temp != NULL)
    {
        ProductNode* product = findProduct(temp->productID);

        if (product != NULL)
        {
            double subtotal = product->data.price * temp->quantity;

            cout << "\nProduct: " << product->data.productName;
            cout << "\nProduct ID: " << temp->productID;
            cout << "\nQuantity: " << temp->quantity;
            cout << "\nPrice: " << product->data.price;
            cout << "\nSubtotal: " << subtotal << endl;

            total += subtotal;
        }

        temp = temp->next;
    }

    cout << "\nTotal Purchase Amount: " << total << endl;

    return total;
}

// --------------------------------------------------
// PLACE ORDER FROM CART INTO QUEUE
// --------------------------------------------------

void placeOrder()
{
    if (cartTop == NULL)
    {
        cout << "\nCannot place order! Shopping Cart is Empty!\n";
        return;
    }

    string customerName;

    cout << "\nEnter Customer Name: ";
    cin.ignore(1000, '\n');
    getline(cin, customerName);

    if (customerName.empty())
    {
        cout << "\nInvalid customer name!\n";
        return;
    }

    // Validate all cart items before changing stock
    CartNode* cartTemp = cartTop;

    while (cartTemp != NULL)
    {
        ProductNode* product = findProduct(cartTemp->productID);

        if (product == NULL)
        {
            cout << "\nA cart product is no longer available. Order cancelled!\n";
            return;
        }

        int totalQuantity = 0;
        CartNode* checkTemp = cartTop;

        while (checkTemp != NULL)
        {
            if (checkTemp->productID == cartTemp->productID)
                totalQuantity += checkTemp->quantity;

            checkTemp = checkTemp->next;
        }

        if (totalQuantity > product->data.stock)
        {
            cout << "\nInsufficient stock. Order cancelled!\n";
            return;
        }

        cartTemp = cartTemp->next;
    }

    // All items are valid; now create queue orders and update stock
    cartTemp = cartTop;
    double purchaseTotal = 0;

    while (cartTemp != NULL)
    {
        ProductNode* product = findProduct(cartTemp->productID);

        OrderNode* newNode = new OrderNode;

        newNode->data.orderID = nextOrderID++;
        newNode->data.customerName = customerName;
        newNode->data.productID = product->data.productID;
        newNode->data.productName = product->data.productName;
        newNode->data.quantity = cartTemp->quantity;
        newNode->data.price = product->data.price;
        newNode->data.totalAmount =
            product->data.price * cartTemp->quantity;

        newNode->next = NULL;

        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        purchaseTotal += newNode->data.totalAmount;

        product->data.stock -= cartTemp->quantity;

        cartTemp = cartTemp->next;
    }

    cout << "\nOrder placed successfully!";
    cout << "\nTotal Purchase Amount: " << purchaseTotal << endl;

    // Empty the cart after successful checkout
    while (cartTop != NULL)
    {
        CartNode* temp = cartTop;
        cartTop = cartTop->next;
        delete temp;
    }
}

// --------------------------------------------------
// PROCESS FIRST ORDER FROM QUEUE
// --------------------------------------------------

void processOrder()
{
    if (front == NULL)
    {
        cout << "\nOrder Queue is Empty!\n";
        return;
    }

    OrderNode* temp = front;

    cout << "\n========== PROCESSING ORDER ==========\n";
    cout << "Order ID: " << temp->data.orderID;
    cout << "\nCustomer: " << temp->data.customerName;
    cout << "\nProduct: " << temp->data.productName;
    cout << "\nQuantity: " << temp->data.quantity;
    cout << "\nTotal Amount: " << temp->data.totalAmount << endl;

    front = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;

    cout << "\nOrder processed successfully!\n";
}

// --------------------------------------------------
// DISPLAY PENDING ORDERS
// --------------------------------------------------

void displayOrders()
{
    if (front == NULL)
    {
        cout << "\nNo Pending Orders!\n";
        return;
    }

    OrderNode* temp = front;

    cout << "\n========== PENDING ORDERS ==========\n";

    while (temp != NULL)
    {
        cout << "\nOrder ID: " << temp->data.orderID;
        cout << "\nCustomer: " << temp->data.customerName;
        cout << "\nProduct: " << temp->data.productName;
        cout << "\nQuantity: " << temp->data.quantity;
        cout << "\nTotal Amount: " << temp->data.totalAmount;
        cout << "\n------------------------------------\n";

        temp = temp->next;
    }
}

// --------------------------------------------------
// CALCULATE PENDING ORDER AMOUNT
// --------------------------------------------------

void calculatePendingAmount()
{
    double total = 0;
    OrderNode* temp = front;

    while (temp != NULL)
    {
        total += temp->data.totalAmount;
        temp = temp->next;
    }

    cout << "\nTotal Pending Order Amount: " << total << endl;
}

// --------------------------------------------------
// SAVE PRODUCTS AND ORDERS
// --------------------------------------------------

void saveData()
{
    ofstream productFile("products.txt");

    if (!productFile.is_open())
    {
        cout << "\nUnable to save products!\n";
        return;
    }

    ProductNode* pTemp = productHead;

    while (pTemp != NULL)
    {
        productFile << pTemp->data.productID << '\n';
        productFile << pTemp->data.productName << '\n';
        productFile << pTemp->data.category << '\n';
        productFile << pTemp->data.price << '\n';
        productFile << pTemp->data.stock << '\n';

        pTemp = pTemp->next;
    }

    productFile.close();

    ofstream orderFile("orders.txt");

    if (!orderFile.is_open())
    {
        cout << "\nUnable to save orders!\n";
        return;
    }

    OrderNode* oTemp = front;

    while (oTemp != NULL)
    {
        orderFile << oTemp->data.orderID << '\n';
        orderFile << oTemp->data.customerName << '\n';
        orderFile << oTemp->data.productID << '\n';
        orderFile << oTemp->data.productName << '\n';
        orderFile << oTemp->data.quantity << '\n';
        orderFile << oTemp->data.price << '\n';
        orderFile << oTemp->data.totalAmount << '\n';

        oTemp = oTemp->next;
    }

    orderFile.close();

    cout << "\nProducts and pending orders saved successfully!\n";
}

// --------------------------------------------------
// LOAD PRODUCTS
// --------------------------------------------------

void loadProducts()
{
    ifstream productFile("products.txt");

    if (!productFile.is_open())
        return;

    string idLine, name, category, priceLine, stockLine;

    while (getline(productFile, idLine))
    {
        if (!getline(productFile, name))
            break;

        if (!getline(productFile, category))
            break;

        if (!getline(productFile, priceLine))
            break;

        if (!getline(productFile, stockLine))
            break;

        Product p;

        p.productID = stoi(idLine);
        p.productName = name;
        p.category = category;
        p.price = stod(priceLine);
        p.stock = stoi(stockLine);

        ProductNode* newNode = new ProductNode;

        newNode->data = p;
        newNode->next = NULL;

        if (productHead == NULL)
        {
            productHead = newNode;
        }
        else
        {
            ProductNode* temp = productHead;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }
    }

    productFile.close();
}

// --------------------------------------------------
// LOAD PENDING ORDERS
// --------------------------------------------------

void loadOrders()
{
    ifstream orderFile("orders.txt");

    if (!orderFile.is_open())
        return;

    string idLine, customer, productIDLine;
    string productName, quantityLine, priceLine, amountLine;

    while (getline(orderFile, idLine))
    {
        if (!getline(orderFile, customer))
            break;

        if (!getline(orderFile, productIDLine))
            break;

        if (!getline(orderFile, productName))
            break;

        if (!getline(orderFile, quantityLine))
            break;

        if (!getline(orderFile, priceLine))
            break;

        if (!getline(orderFile, amountLine))
            break;

        OrderNode* newNode = new OrderNode;

        newNode->data.orderID = stoi(idLine);
        newNode->data.customerName = customer;
        newNode->data.productID = stoi(productIDLine);
        newNode->data.productName = productName;
        newNode->data.quantity = stoi(quantityLine);
        newNode->data.price = stod(priceLine);
        newNode->data.totalAmount = stod(amountLine);

        newNode->next = NULL;

        if (front == NULL)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        if (newNode->data.orderID >= nextOrderID)
            nextOrderID = newNode->data.orderID + 1;
    }

    orderFile.close();
}

// --------------------------------------------------
// CLEAR ALL MEMORY
// --------------------------------------------------

void clearMemory()
{
    while (productHead != NULL)
    {
        ProductNode* temp = productHead;
        productHead = productHead->next;
        delete temp;
    }

    while (cartTop != NULL)
    {
        CartNode* temp = cartTop;
        cartTop = cartTop->next;
        delete temp;
    }

    while (front != NULL)
    {
        OrderNode* temp = front;
        front = front->next;
        delete temp;
    }

    rear = NULL;
}

// --------------------------------------------------
// MAIN FUNCTION
// --------------------------------------------------

int main()
{
    int choice;

    loadProducts();
    loadOrders();

    cout << "\n========================================";
    cout << "\n ONLINE SHOPPING AND ORDER MANAGEMENT";
    cout << "\n========================================\n";

    do
    {
        cout << "\n=============== MAIN MENU ===============\n";
        cout << "1. Register Product\n";
        cout << "2. Display Products\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Search Products\n";
        cout << "6. Sort Products\n";
        cout << "7. Add Product to Cart\n";
        cout << "8. Remove Last Cart Item\n";
        cout << "9. Display Shopping Cart\n";
        cout << "10. Place Order / Checkout\n";
        cout << "11. Process Next Order\n";
        cout << "12. Display Pending Orders\n";
        cout << "13. Calculate Pending Order Amount\n";
        cout << "14. Save All Data\n";
        cout << "15. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addProduct();
            break;

        case 2:
            displayProducts();
            break;

        case 3:
            updateProduct();
            break;

        case 4:
            deleteProduct();
            break;

        case 5:
            searchProducts();
            break;

        case 6:
            sortingMenu();
            break;

        case 7:
            addToCart();
            break;

        case 8:
            removeFromCart();
            break;

        case 9:
            displayCart();
            break;

        case 10:
            placeOrder();
            break;

        case 11:
            processOrder();
            break;

        case 12:
            displayOrders();
            break;

        case 13:
            calculatePendingAmount();
            break;

        case 14:
            saveData();
            break;

        case 15:
            saveData();
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 15);

    clearMemory();

    return 0;
}
