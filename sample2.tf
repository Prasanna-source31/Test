provider "azurerm" {
  features = {}
}

resource "azurerm_resource_group" "aks" {
  name     = "aks-resources"
  location = "East US"
}

resource "azurerm_kubernetes_cluster" "aks" {
  name                = "example-aks"
  location            = azurerm_resource_group.aks.location
  resource_group_name = azurerm_resource_group.aks.name

  dns_prefix      = "exampleaks"
  node_resource_group = "aks-nodes"

  default_node_pool {
    name       = "default"
    node_count = 1
    vm_size    = "Standard_D2_v2"
  }

  identity {
    type = "SystemAssigned"
  }
}

# Other configurations for AKS, like networking, RBAC, etc.
