class ChangeAssociationSensorSensorTypes < ActiveRecord::Migration
  def self.up
	remove_column :sensor_types, :sensor_id
	add_column :sensors, :sensor_type_id, :integer
  end

  def self.down
	add_column :sensor_types, :sensor_id, :integer
	remove_column :sensors, :sensor_type
  end
end
