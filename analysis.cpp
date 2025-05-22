/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2025 Tec de Monterrey
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @file analysis.cpp
 * @brief Implementación de funciones para análisis de texto como búsqueda de patrones, palíndromos y substrings comunes.
 */

#include "analysis.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @brief Lee el contenido completo de un archivo de texto.
 * @param filename Ruta del archivo a leer.
 * @return Cadena con el contenido del archivo.
 */
string read_file_content(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

/**
 * @brief Verifica si un patrón está contenido dentro de un texto.
 * @param text Texto donde se buscará.
 * @param pattern Patrón a buscar.
 * @return Par (bool, posición 1-based). True si se encuentra el patrón, y la posición; false si no.
 */
pair<bool, size_t> contains_pattern(const string &text, const string &pattern)
{
    size_t pos = text.find(pattern);
    return (pos != string::npos) ? make_pair(true, pos + 1) : make_pair(false, static_cast<size_t>(0));
}

/**
 * @brief Expande desde el centro para encontrar el palíndromo más largo posible.
 * @param text Texto a evaluar.
 * @param left Índice inicial izquierdo.
 * @param right Índice inicial derecho.
 * @return Par con los índices (inclusive) donde inicia y termina el palíndromo.
 */
pair<int, int> expand_center(const string &text, int left, int right)
{
    while (left >= 0 && right < text.size() && text[left] == text[right])
    {
        --left;
        ++right;
    }
    // Retornamos el rango válido (inclusive)
    return {left + 1, right - 1};
}

/**
 * @brief Encuentra el palíndromo más largo dentro del texto.
 * @param text Texto a analizar.
 * @return Par (inicio, fin) 1-based del palíndromo más largo.
 */
pair<int, int> longest_palindrome(const string &text)
{
    if (text.empty())
        return {1, 1};

    int start = 0, end = 0;
    for (int i = 0; i < text.size(); ++i)
    {
        // Casos para palíndromos impares (aba)
        auto [l1, r1] = expand_center(text, i, i);
        // Casos para palíndromos pares (abba)
        auto [l2, r2] = expand_center(text, i, i + 1);

        if (r1 - l1 > end - start)
        {
            start = l1;
            end = r1;
        }
        if (r2 - l2 > end - start)
        {
            start = l2;
            end = r2;
        }
    }
    // Convertimos de 0-based a 1-based
    return {start + 1, end + 1};
}

/**
 * @brief Encuentra el substring común más largo entre dos textos.
 * @param text1 Primer texto.
 * @param text2 Segundo texto.
 * @return Par (inicio, fin) 1-based del substring común más largo en el primer texto.
 */
pair<int, int> longest_common_substring(const string &text1, const string &text2)
{
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen)
                {
                    maxLen = dp[i][j];
                    endIdx = i;
                }
            }
        }
    }
    return {endIdx - maxLen + 1, endIdx};
}
