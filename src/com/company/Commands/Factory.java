package com.company.Commands;

import com.company.Commands.ICommand;

import java.util.*;
import java.lang.reflect.*;

public class Factory {
	public static Factory GetInstance() {
		if (s_instance == null) {
			s_instance = new Factory();
		}
		return s_instance;
	}
	public ICommand CreateCommand(String name, String input) {
		Method method = m_factoryMap.get(name);
		if (method != null) {
			try {
				return (ICommand)method.invoke(null, name, input);
			}
			catch (Exception ex) {
				return null;
			}
		}
		return null;
	}
	public void Register(String name, Method fn) {
		m_factoryMap.put(name, fn);
	}
	/*********************************************************************************
	* Default constructor
	* null
	**********************************************************************************
	*/
	private static Factory s_instance;
	private Factory() {

	}
	private HashMap<String, Method> m_factoryMap;
};
