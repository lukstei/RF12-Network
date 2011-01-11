class AddAnalogToSensorType < ActiveRecord::Migration
  def self.up
	add_column :sensor_types, :is_analog, :boolean
	remove_column :sensor_types, :interface
  end

  def self.down
	remove_column :sensor_types, :is_analog
	add_column :sensor_types, :interface, :string 
  end
end
