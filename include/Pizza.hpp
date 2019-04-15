/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
    #define PIZZA_HPP_

    /**
     * \namespace Pizza
     * \brief All Data Pizza
     */
	namespace Pizza {

        /**
         * \enum Type
         * \brief Type of Pizza
         */
		enum Type {
			Regina = 1,/*!< Regina pizza*/
			Margarita = 2,/*!< Margarita pizza */
			Americana = 4,/*!< Americana pizza */
			Fantasia = 8,/*!< Fantasia pizza */
		};

        /**
         * \enum Size
         * \brief Size of Pizza
         */
		enum Size {
			S = 1,/*!< Small size */
			M = 2,/*!< Medium size */
			L = 4,/*!< Large size */
			XL = 8,/*!< Extra large size */
			XXL = 16,/* Extra extra large size */
		};

        /**
         * \struct Pizza::Pizza
         * \brief Pizza Data (type and size)
         */
		struct Pizza {
			const enum Type _type;/*!< Type of the pizza */
			const enum Size _size;/*!< Size of the pizza */
		};

	};

#endif /* !PIZZA_HPP_ */
