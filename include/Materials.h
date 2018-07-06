#pragma once
#include "Angel/Angel.h"

class Material {
public:
	vec4 light_ambient;
	vec4 light_diffuse;
	vec4 light_specular;
	vec4 material_ambient;
	vec4 material_diffuse;
	vec4 material_specular;
	GLfloat material_shininess;

	/// http://devernay.free.fr/cours/opengl/materials.html
	enum type {
		emerald = 0,
		obsidian = 1,
		jade = 2,
		pearl = 3,
		ruby = 4,
		turquoise = 5,
		brass = 6,
		red_plastic = 7,
		gold = 8
	};

	Material() = default;

	Material(type t) {
		switch (t	) {
		default:
		case Material::emerald:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.0215, 0.1745, 0.0215, 1);
			material_diffuse = vec4(0.07568, 0.61424, 0.07568, 1);
			material_specular = vec4(0.633, 0.727811, 0.633, 1);
			material_shininess = 0.6 * 128;
			break;
		case Material::obsidian:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.05375, 0.05, 0.06625, 1);
			material_diffuse = vec4(0.18275, 0.17, 0.22525, 1);
			material_specular = vec4(0.332741, 0.328634, 0.346435, 1);
			material_shininess = 0.3 * 128;
			break;
		case Material::jade:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.135, 0.2225, 0.1575, 1);
			material_diffuse = vec4(0.54, 0.89, 0.63, 1);
			material_specular = vec4(0.316228, 0.316228, 0.316228, 1);
			material_shininess = 0.1 * 128;
			break;
		case Material::pearl:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.25, 0.20725, 0.20725, 1);
			material_diffuse = vec4(1, 0.829, 0.829, 1);
			material_specular = vec4(0.296648, 0.296648, 0.296648, 1);
			material_shininess = 0.1 * 128;
			break;
		case Material::ruby:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.1745, 0.01175, 0.01175, 1);
			material_diffuse = vec4(0.61424, 0.04136, 0.04136, 1);
			material_specular = vec4(0.727811, 0.626959, 0.626959, 1);
			material_shininess = 0.6 * 128;
			break;
		case Material::turquoise:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.1, 0.18725, 0.1745, 1);
			material_diffuse = vec4(0.396, 0.74151, 0.69102, 1);
			material_specular = vec4(0.297254, 0.30829, 0.306678, 1);
			material_shininess = 0.1 * 128;
			break;
		case Material::brass:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(1, 1, 1, 1);
			material_ambient = vec4(0.329412, 0.223529, 0.027451, 1);
			material_diffuse = vec4(0.780392, 0.568627, 0.113725, 1);
			material_specular = vec4(0.992157, 0.941176, 0.807843, 1);
			material_shininess = 0.21794872 * 128;
			break;
		case Material::red_plastic:
			light_ambient = vec4(1, 1, 1, 1);
			light_diffuse = vec4(1, 1, 1, 1);
			light_specular = vec4(0, 0, 0, 1);
			material_ambient = vec4(0.0, 0.0, 0.0, 1);
			material_diffuse = vec4(0.5, 0.0, 0.0, 1);
			material_specular = vec4(0.7, 0.6, 0.6, 1);
			material_shininess = 0.25 * 128;
			break;
		case Material::gold:
			light_ambient = vec4(1, 1, 1, 1.0);
			light_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
			light_specular = vec4(1.0, 1.0, 1.0, 1.0);
			material_ambient = vec4(0.24725, 0.1995, 0.0745, 1.0);
			material_diffuse = vec4(0.75164, 0.60648, 0.22648, 1.0);
			material_specular = vec4(0.628281, 0.555802, 0.366065, 1.0);
			material_shininess = 0.4 * 128;
			break;
		}
	}
};