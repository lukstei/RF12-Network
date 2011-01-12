class RemoveSpiAndAddInterfaceId < ActiveRecord::Migration
  def self.up
	remove_column :interfaces, :spi
	add_column :sensor_types, :interface_id, :integer
  end

  def self.down
	add_column :interfaces, :spi, :boolean
	remove_column :sensor_types, :interface_id
  end
end
