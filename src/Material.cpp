#include <Material.h>
#include "stdio.h"

Material::Material() {
	//nom = "Inconnu";
}

Material::Material(string pNom){
	nom = pNom;
}

string Material::getNom(){
	return nom;
}


float Material::getAmbientR(){
	return ambiant_r;
}

float Material::getAmbientG(){
	return ambiant_g;
}

float Material::getAmbientB(){
	return ambiant_b;
}


float Material::getDiffuseR(){
	return diffuse_r;
}

float Material::getDiffuseG(){
	return diffuse_g;
}

float Material::getDiffuseB(){
	return diffuse_b;
}

float Material::getSpecularR(){
	return specular_r;
}

float Material::getSpecularG(){
	return specular_g;
}

float Material::getSpecularB(){
	return specular_b;
}

float Material::getSpecularExponent(){
	return Ns;
}

float Material::getDissolve(){
	return d;
}

float Material::getIndiceOfRefraction() {
	return Ni;
}

int Material::getIlluminationModel() {
	return illum;
}

string Material::getMapKd() {
	return mapKd;
}

void Material::setNom(string pNom){
	nom = pNom;
}

void Material::setAmbient(float pR, float pG, float pB){
	ambiant_r = pR;
	ambiant_g = pG;
	ambiant_b = pB;
}

void Material::setSpecular(float pR, float pG, float pB){
	specular_r = pR;
	specular_g = pG;
	specular_b = pB;
}

void Material::setDiffuse(float pR, float pG, float pB){
	diffuse_r = pR;
	diffuse_g = pG;
	diffuse_b = pB;
}

void Material::setSpecularExponent(float pNs){
	Ns = pNs;
}

void Material::setDissolve(float pFactor) {
	d = pFactor;
}

void Material::setIndiceOfRefraction(float pNi) {
	Ni = pNi;
}

void Material::setIlluminationModel(int pIllum) {
	illum = pIllum;
}

void Material::setMapKd(string pFullFilename) {
	mapKd = pFullFilename;
}