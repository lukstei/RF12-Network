class AddIds < ActiveRecord::Migration
  def self.up
	add_column :sensors, :task_id, :integer
	add_column :sensors, :station_id, :integer
	add_column :sensor_types, :sensor_id, :integer
  end

  def self.down
	remove_column :sensors, :task_id, :station_id
	remove_column :sensor_types, :sensor_id
  end
end
