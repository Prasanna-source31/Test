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
deny[msg] {
  input.resource.type == "azurerm_virtual_machine"
  input.resource.size != "Standard_DS2_v2"
  msg = "Virtual Machine size should be 'Standard_DS2_v2'"
}

deny[msg] {
  input.resource.type == "azurerm_function_app"
  input.resource.version != "~3"
  msg = "Function App version should be '~3'"
}

deny[msg] {
  input.resource.type == "azurerm_key_vault"
  input.resource.enabled_for_disk_encryption != true
  msg = "Key Vault should be enabled for disk encryption"
}

deny[msg] {
  input.resource.type == "azurerm_key_vault"
  input.resource.sku_name != "standard"
  msg = "Key Vault SKU should be 'standard'"
}

deny[msg] {
  input.resource.type == "azurerm_cosmosdb_account"
  input.resource.offer_type != "Standard"
  msg = "Cosmos DB offer type should be 'Standard'"
}

deny[msg] {
  input.resource.type == "azurerm_data_factory"
  input.resource.location != "East US"
  msg = "Data Factory should be deployed in 'East US' region"
}
deny[msg] {
  input.resource.type == "azurerm_application_gateway"
  input.resource.skus[0].capacity < 2
  msg = "Application Gateway capacity should be at least 2"
}

deny[msg] {
  input.resource.type == "azurerm_data_lake_storage_gen2"
  input.resource.hierarchical_namespace != true
  msg = "Data Lake Storage Gen2 should have hierarchical namespace enabled"
}

deny[msg] {
  input.resource.type == "azurerm_sql_server"
  input.resource.version != "12.0"
  msg = "SQL Server version should be '12.0'"
}

deny[msg] {
  input.resource.type == "azurerm_service_principal"
  not startswith(input.resource.display_name, "sp_")
  msg = "Service Principal display name should start with 'sp_'"
}

deny[msg] {
  input.resource.type == "azurerm_monitor_autoscale_setting"
  input.resource.scale_out_cooldown < 300
  msg = "Autoscale Setting scale-out cooldown should be at least 300 seconds"
}

deny[msg] {
  input.resource.type == "azurerm_key_vault_secret"
  not endswith(input.resource.name, "_secret")
  msg = "Key Vault Secret name should end with '_secret'"
}
deny[msg] {
  input.resource.type == "azurerm_cosmosdb_account"
  not contains(input.resource.capabilities, "EnableCassandra")
  msg = "Cosmos DB should have Cassandra API enabled"
}

deny[msg] {
  input.resource.type == "azurerm_virtual_network"
  length(input.resource.address_space) < 2
  msg = "Virtual Network should have at least 2 address spaces"
}

deny[msg] {
  input.resource.type == "azurerm_network_security_group"
  input.resource.security_rule[rule] {
    rule = input.resource.security_rule[_]
    rule.access == "Allow"
    rule.priority > 100
  }
  msg = "Network Security Group should not have 'Allow' rules with priority greater than 100"
}

deny[msg] {
  input.resource.type == "azurerm_eventhub_namespace"
  input.resource.sku.name != "Standard"
  msg = "Event Hub Namespace SKU should be 'Standard'"
}

deny[msg] {
  input.resource.type == "azurerm_logic_app_workflow"
  not contains(input.resource.dependent_parameter, "Microsoft.Logic/workflows/triggers")
  msg = "Logic App Workflow should depend on a trigger"
}

deny[msg] {
  input.resource.type == "azurerm_app_service_environment"
  input.resource.multi_role_pool[0].name != "default"
  msg = "App Service Environment multi-role pool should be named 'default'"
}
deny[msg] {
  input.resource.type == "azurerm_key_vault"
  not contains(input.resource.sku.family, "A")
  msg = "Key Vault SKU family should be 'A'"
}

deny[msg] {
  input.resource.type == "azurerm_data_lake_store"
  input.resource.firewall_rules[rule] {
    rule = input.resource.firewall_rules[_]
    rule.start_ip_address == "0.0.0.0"
  }
  msg = "Data Lake Store should not allow '0.0.0.0' in firewall rules"
}

deny[msg] {
  input.resource.type == "azurerm_data_factory"
  input.resource.enable_auto_publish != true
  msg = "Data Factory should have auto-publish enabled"
}

deny[msg] {
  input.resource.type == "azurerm_stream_analytics_job"
  input.resource.outputs[output] {
    output = input.resource.outputs[_]
    not contains(output.datasource.resource_id, "blob.core.windows.net")
  }
  msg = "Stream Analytics Job output should be directed to Azure Blob Storage"
}

deny[msg] {
  input.resource.type == "azurerm_application_gateway"
  input.resource.backend_address_pool[pool] {
    pool = input.resource.backend_address_pool[_]
    pool.backend_address[addr] {
      addr = pool.backend_address[_]
      not endswith(addr.fqdn, ".azurewebsites.net")
    }
  }
  msg = "Application Gateway backend pool should not include Azure Websites"
}
deny[msg] {
  input.resource.type == "azurerm_virtual_machine"
  input.resource.os_profile.windows_config.should_run_custom_script_extension != true
  msg = "Windows VMs should have the Custom Script Extension enabled"
}

deny[msg] {
  input.resource.type == "azurerm_cosmosdb_account"
  not input.resource.consistency_policy[0].max_interval == "200"
  msg = "Cosmos DB consistency policy max interval should be set to '200'"
}

deny[msg] {
  input.resource.type == "azurerm_service_principal"
  not input.resource.app_id != input.resource.object_id
  msg = "Service Principals should have distinct App ID and Object ID"
}

deny[msg] {
  input.resource.type == "azurerm_traffic_manager_profile"
  not input.resource.monitor_config.protocol == "HTTPS"
  msg = "Traffic Manager should use HTTPS for health checks"
}

deny[msg] {
  input.resource.type == "azurerm_app_service"
  input.resource.identity.identity_ids[_] == "system"
  msg = "App Service should not use 'system' identity"
}

deny[msg] {
  input.resource.type == "azurerm_sql_server"
  input.resource.version != "12.0"
  msg = "SQL Server version should be '12.0'"
}
