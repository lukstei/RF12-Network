class AddNameToSensors < ActiveRecord::Migration
  def self.up
	add_column :sensors, :name, :string 
  end

  def self.down
	remove_column :sensors, :name 
  end
end
