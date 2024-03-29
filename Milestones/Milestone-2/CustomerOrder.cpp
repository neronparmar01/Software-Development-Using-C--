// Name: Neron Parmar
// Seneca Student ID: 171690217
// Seneca email: nparmar22@myseneca.ca
// Date of completion: 11/18/23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;
namespace sdds {



	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities util{};
		size_t next_pos = 0;
		bool more = true;



		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		int count = 0;



		size_t new_pos = next_pos;
		bool newMore = more;
		while (newMore) {



			string token = util.extractToken(str, new_pos, newMore);
			count++;
		}


		m_lstItem = new Item * [count];
		while (more) {
			m_lstItem[m_cntItem] = new Item(util.extractToken(str, next_pos, more));
			m_cntItem++;
		}
		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
	}


	CustomerOrder::CustomerOrder(const CustomerOrder& other) {
		throw "Copy constructor is not allowed for CustomerOrder";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			m_name = move(src.m_name);
			m_product = move(src.m_product);
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = src.m_lstItem;
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;

		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!(m_lstItem[i]->m_isFilled)) {
				result = false;
			}
		}
		return result;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		size_t count = 0;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if ((m_lstItem[i]->m_isFilled) && (m_lstItem[i]->m_itemName == itemName)) {
				return true;
			}

			if (m_lstItem[i]->m_itemName == itemName) {
				count++;
			}
		}
		if (count == 0) {
			return true;
		}

		return false;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if ((m_lstItem[i]->m_itemName == station.getItemName()) && !(isItemFilled(m_lstItem[i]->m_itemName))) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[";
			os.width(6);
			os.fill('0');
			os << m_lstItem[i]->m_serialNumber << "] ";
			os.width(m_widthField);
			os.fill(' ');
			os << left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << endl;
		}
	}


}