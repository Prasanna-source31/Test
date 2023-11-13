provider "azurerm" {
  features = {}
}

resource "azurerm_resource_group" "example" {
  name     = "example-resources"
  location = "East US"
}

resource "azurerm_virtual_network" "example" {
  name                = "example-network"
  address_space       = ["10.0.0.0/16"]
  location            = azurerm_resource_group.example.location
  resource_group_name = azurerm_resource_group.example.name
}

# More resources for subnets, network security groups, etc.

# Deploying App Service and Database in a different module

module "webapp" {
  source              = "./modules/webapp"
  resource_group_name = azurerm_resource_group.example.name
  location            = azurerm_resource_group.example.location
  vnet_subnet_id      = azurerm_subnet.example.id
}

module "database" {
  source              = "./modules/database"
  resource_group_name = azurerm_resource_group.example.name
  location            = azurerm_resource_group.example.location
  vnet_subnet_id      = azurerm_subnet.example.id
}
