C program that implements a simple machine learning algorithm for predicting house prices based on historical data.

The price of the house (y) can depend on various attributes: number of bedrooms (x1 ), total
size of the house (x2 ), number of baths (x3 ), and the year the house was built (x4 ). If these are the
only variables that affect price, then the price of the house can be computed by the following equation:

y = w0 + w1 * x1 + w2 * x2 + w3 * x3 + w4 * y4 (1)

Given a house, we might know the attributes of the house (i.e., x1 , x2 , x3 , x4 ), however, we
don’t know the weights for these attributes: w0 , w1 , w2 , w3 and w4. For instance, having 2 baths
may be more important to some people than others, so the weight of that factor can change based on the
value people attach to it.

Using the training data, we can learn the weights using the below equation:

W = (X T * X)−1 * XT * Y (3)

XT is the transpose of the matrix X. X-1 is the inverse of the matrix X, so (X T * X)−1 is the
inverse of (X T * X).

The goal is to learn the weights for the attributes of the house from lots of training data.
Training data is data that is known (or presumed) to be fully diagnostic and
representative of what we want to test that is used to 'teach' the machine algorithm. The algorithm will
then take what it has 'learned' from the training data and later apply it to testing data, data where some
of the factors and variables are not known, and will estimate the most likely values for those factors
and variables.
