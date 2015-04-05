package com.company.Commands;

import java.lang.reflect.*;
import java.util.*;

public class Categorizer {
	private class Category {
		Category(String name, Method fn) {
			Name = name;
			ValidateFn = fn;
		}
		public String Name;
		public Method ValidateFn;
	}
	private Categorizer() {
		m_categoryList = new Vector<Category>();
	}
	public static Categorizer GetInstance() {
		if (s_instance == null) {
			s_instance = new Categorizer();
		}
		return s_instance;
	}
	public String CreateCategory(String input) {
		for (Category cat : m_categoryList) {
			boolean rightCat = false;
			try {
				rightCat = (boolean)cat.ValidateFn.invoke(null, input);
			}
			catch (Exception ex) {
			}
			if (rightCat) {
				return cat.Name;
			}
		}
		return "Uncategorized";
	}
	public void Register(String name, Method fn) {
		m_categoryList.add(new Category(name, fn));

	}
	/*********************************************************************************
	* Default constructor
	* null
	**********************************************************************************
	*/
	private static Categorizer s_instance;
	private Vector<Category> m_categoryList;
};
