provider "azurerm" {
  features = {}
}

resource "azurerm_resource_group" "function" {
  name     = "function-resources"
  location = "East US"
}

resource "azurerm_storage_account" "function" {
  name                     = "funcstorage"
  resource_group_name      = azurerm_resource_group.function.name
  location                 = azurerm_resource_group.function.location
  account_tier             = "Standard"
  account_replication_type = "LRS"
}

resource "azurerm_function_app" "example" {
  name                      = "example-func"
  location                  = azurerm_resource_group.function.location
  resource_group_name       = azurerm_resource_group.function.name
  storage_account_name      = azurerm_storage_account.function.name
  app_service_plan_id       = azurerm_app_service_plan.example.id
  version                   = "~3"
  os_type                   = "linux"
  runtime                   = "python"
  site_config {
    linux_fx_version = "PYTHON|3.8"
  }

  app_settings = {
    "FUNCTIONS_WORKER_RUNTIME" = "python"
    "WEBSITE_RUN_FROM_PACKAGE" = "https://${azurerm_storage_account.example.primary_blob_endpoint}${azurerm_storage_container.example.name}/example.zip"
  }
}

resource "azurerm_storage_container" "example" {
  name                  = "example-container"
  storage_account_name  = azurerm_storage_account.example.name
  container_access_type = "private"
}
