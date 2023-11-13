package azure.terraform

deny[msg] {
  input.resource.type == "azurerm_resource_group"
  not startswith(input.resource.name, "example-resources")
  msg = "Resource group names should start with 'example-resources'"
}

deny[msg] {
  input.resource.type == "azurerm_kubernetes_cluster"
  input.resource.default_node_pool.vm_size != "Standard_D2_v2"
  msg = "AKS default node pool should use 'Standard_D2_v2' VM size"
}

deny[msg] {
  input.resource.type == "azurerm_kubernetes_cluster"
  input.resource.default_node_pool.node_count != 1
  msg = "AKS default node pool should have exactly 1 node"
}

deny[msg] {
  input.resource.type == "azurerm_function_app"
  not contains(input.resource.runtime, "python")
  msg = "Function App should use Python runtime"
}

deny[msg] {
  input.resource.type == "azurerm_storage_account"
  input.resource.account_tier != "Standard"
  msg = "Storage account tier should be 'Standard'"
}

deny[msg] {
  input.resource.type == "azurerm_storage_account"
  input.resource.account_replication_type != "LRS"
  msg = "Storage account replication type should be 'LRS'"
}

# Additional rules can be added based on specific requirements
